#include "netlink.h"

/**
 * What to do when an error occurs during communcation
 * Copied from netlink.c
 */
int netlink_print_error(struct sockaddr_nl* nla __maybe_unused,
                        struct nlmsgerr* nlerr, void* arg __maybe_unused) {
    if (nlerr->error != -95)
        fprintf(stderr, "Error during communication: %s\n",
                strerror(-nlerr->error));

    return NL_STOP;
}

/**
 * What to do when communications are stopped (idk when this happens)
 * Copied from netlink.c
 */
int netlink_stop_callback(struct nl_msg* msg, void* arg __maybe_unused) {
    struct nlmsghdr* nlh = nlmsg_hdr(msg);
    int* error = nlmsg_data(nlh);

    if (*error)
        fprintf(stderr, "Error during communication: %s\n", strerror(-*error));

    return NL_STOP;
}

int tq_callback(struct nl_msg* msg, void* arg) {
    struct nlattr* attrs[61];
    struct nlmsghdr* nlh = nlmsg_hdr(msg);
    struct genlmsghdr* ghdr;

    struct opts* options = arg;

    // Validate header
    if (!genlmsg_valid_hdr(nlh, 0))
        throw_error(NL_PARSE_ERR, "Received invalid data from kernel.\n");

    // Parse data into attrs array
    ghdr = nlmsg_data(nlh);
    if (nla_parse(attrs, 60, genlmsg_attrdata(ghdr, 0), genlmsg_len(ghdr),
                  batadv_netlink_policy))
        throw_error(NL_PARSE_ERR, "Received invalid data from kernel.\n");

    // Process data
    uint8_t* orig = nla_data(attrs[BATADV_ATTR_ORIG_ADDRESS]);
    uint8_t* neigh = nla_data(attrs[BATADV_ATTR_NEIGH_ADDRESS]);
    int tq = nla_get_u8(attrs[BATADV_ATTR_TQ]);

    // Filter out multi-hop OGMs
    if (orig[0] != neigh[0] || orig[1] != neigh[1] || orig[2] != neigh[2] ||
        orig[3] != neigh[3] || orig[4] != neigh[4] || orig[5] != neigh[5])
        return NL_OK;

    if (options->mode == LOG) {
        // Get current time
        time_t now;
        time(&now);
        char* recv_time = ctime(&now);
        recv_time[24] = 0;  // Remove newline

        // Save data to file
        save_tq(options->file_name, orig, tq, recv_time);
    } else if (options->mode == PRINT) {
        char mac_str[18];
        mac_to_str(mac_str, orig);
        if (strcmp(options->mac, mac_str) == 0) printf("%d\n", tq);
    } else {
    }

    return NL_OK;
}

void netlink_comm_loop(struct opts* options) {
    // Prepare for communication

    /// Based on functions.c - check_mesh_iface
    unsigned int mesh_ifindex = if_nametoindex("bat0");

    /// Based on netlink.c - netlink_create
    struct nl_sock* sock = nl_socket_alloc();
    if (!sock) throw_error(NL_ALLOC_ERR, "Error creating nl_sock\n");
    genl_connect(sock);

    /// Based on netlink.c - netlink_create
    struct nl_cb* cb = nl_cb_alloc(NL_CB_DEFAULT);
    if (!cb) throw_error(NL_ALLOC_ERR, "Error creating nl_cb\n");

    /// Based on netlink.c - netlink_create
    int batadv_family = genl_ctrl_resolve(sock, "batadv");

    // Set up callbacks for receiving data

    struct nl_msg* msg;

    /// Based on/copied from netlink.c - netlink_print_common
    nl_cb_set(cb, NL_CB_VALID, NL_CB_CUSTOM, tq_callback, options);
    nl_cb_set(cb, NL_CB_FINISH, NL_CB_CUSTOM, netlink_stop_callback, NULL);
    nl_cb_err(cb, NL_CB_CUSTOM, netlink_print_error, NULL);

    // Ask kernel for data (data is processed in the callback)

    unsigned int i = 0;  // Assumption: this program will not be run for
                         // over 4.3 billion iterations

    /// Based on netlink.c - netlink_print_common
    while (options->repetitions == -1 || i < options->repetitions) {
        msg = nlmsg_alloc();
        if (!msg) throw_error(NL_ALLOC_ERR, "Error creating nl_msg\n");
        genlmsg_put(msg, NL_AUTO_PID, NL_AUTO_SEQ, batadv_family, 0, NLM_F_DUMP,
                    8, 1);
        nla_put_u32(msg, 3, mesh_ifindex);
        nl_send_auto_complete(sock, msg);
        nlmsg_free(msg);
        nl_recvmsgs(sock, cb);
        usleep(1000000 * options->wait);
        i++;
    }
}
