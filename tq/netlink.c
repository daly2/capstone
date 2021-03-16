/**
 * Parts of this program are copied from and/or heavily influenced by batctl
 *  and have the following copyright:
 *
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Andreas Langer <an.langer@gmx.de>, Marek Lindner <mareklindner@neomailbox.ch>
 *
 * License-Filename: LICENSES/preferred/GPL-2.0
 *
 */

#include "netlink.h"

/**
 * What to do when an error occurs during communcation
 *
 * Based on netlink.c: netlink_print_error
 */
int netlink_print_error(struct sockaddr_nl* nla __maybe_unused,
                        struct nlmsgerr* nlerr, void* arg __maybe_unused) {
    if (nlerr->error != -95)
        fprintf(stderr, "Error during communication: %s\n",
                strerror(-nlerr->error));

    return NL_STOP;
}

/**
 * What to do when communications are stopped
 *
 * Based on netlink.c: netlink_stop_callback
 */
int netlink_stop_callback(struct nl_msg* msg, void* arg __maybe_unused) {
    struct nlmsghdr* nlh = nlmsg_hdr(msg);
    int* error = nlmsg_data(nlh);

    if (*error)
        fprintf(stderr, "Error during communication: %s\n", strerror(-*error));

    return NL_STOP;
}

/**
 * Process data received from the kernel
 *
 * Based on originators.c: originators_callback
 */
int tq_callback(struct nl_msg* msg, void* arg) {
    struct nlattr* attrs[NUM_BATADV_ATTR];
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
        // Convert MAC to string
        char mac_str[18];
        mac_to_str(mac_str, orig);

        // Compare MAC, and if it matches, print the TQ
        if (strcmp(options->mac, mac_str) == 0) printf("%d\n", tq);
    } else
        throw_error(UNDEFINED_BEHAVIOR_ERR, "Unrecognized program mode: %d",
                    options->mode);

    return NL_OK;
}

/**
 * Communicate with the kernel and request the TQ data
 *
 * Based on:
 *  functions.c: check_mesh_iface
 *  netlink.c: netlink_create netlink_print_common
 */
void netlink_comm_loop(struct opts* options) {
    // Find interface index
    unsigned int mesh_ifindex = if_nametoindex("bat0");

    // Create and connect nl_sock
    struct nl_sock* sock = nl_socket_alloc();
    if (!sock) throw_error(NL_ALLOC_ERR, "Error creating nl_sock\n");
    genl_connect(sock);

    // Create nl_cb
    struct nl_cb* cb = nl_cb_alloc(NL_CB_DEFAULT);
    if (!cb) throw_error(NL_ALLOC_ERR, "Error creating nl_cb\n");

    // Determine family for later use
    int batadv_family = genl_ctrl_resolve(sock, "batadv");

    // Set up callbacks for receiving data
    nl_cb_set(cb, NL_CB_VALID, NL_CB_CUSTOM, tq_callback, options);
    nl_cb_set(cb, NL_CB_FINISH, NL_CB_CUSTOM, netlink_stop_callback, NULL);
    nl_cb_err(cb, NL_CB_CUSTOM, netlink_print_error, NULL);

    // Assumption: this program will not be run for over 4.3 billion iterations
    unsigned int i = 0;

    // Ask kernel for data (data is processed in the callback)
    struct nl_msg* msg;
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
