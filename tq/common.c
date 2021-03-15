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

#include "main.h"

/**
 * Format of a batman-adv message received from netlink
 * Copied from netlink.c
 */
struct nla_policy batadv_netlink_policy[NUM_BATADV_ATTR] = {
    [BATADV_ATTR_VERSION] = {.type = NLA_STRING},
    [BATADV_ATTR_ALGO_NAME] = {.type = NLA_STRING},
    [BATADV_ATTR_MESH_IFINDEX] = {.type = NLA_U32},
    [BATADV_ATTR_MESH_IFNAME] = {.type = NLA_STRING, .maxlen = IFNAMSIZ},
    [BATADV_ATTR_MESH_ADDRESS] = {.type = NLA_UNSPEC,
                                  .minlen = ETH_ALEN,
                                  .maxlen = ETH_ALEN},
    [BATADV_ATTR_HARD_IFINDEX] = {.type = NLA_U32},
    [BATADV_ATTR_HARD_IFNAME] = {.type = NLA_STRING, .maxlen = IFNAMSIZ},
    [BATADV_ATTR_HARD_ADDRESS] = {.type = NLA_UNSPEC,
                                  .minlen = ETH_ALEN,
                                  .maxlen = ETH_ALEN},
    [BATADV_ATTR_ORIG_ADDRESS] = {.type = NLA_UNSPEC,
                                  .minlen = ETH_ALEN,
                                  .maxlen = ETH_ALEN},
    [BATADV_ATTR_TPMETER_RESULT] = {.type = NLA_U8},
    [BATADV_ATTR_TPMETER_TEST_TIME] = {.type = NLA_U32},
    [BATADV_ATTR_TPMETER_BYTES] = {.type = NLA_U64},
    [BATADV_ATTR_TPMETER_COOKIE] = {.type = NLA_U32},
    [BATADV_ATTR_PAD] = {.type = NLA_UNSPEC},
    [BATADV_ATTR_ACTIVE] = {.type = NLA_FLAG},
    [BATADV_ATTR_TT_ADDRESS] = {.type = NLA_UNSPEC,
                                .minlen = ETH_ALEN,
                                .maxlen = ETH_ALEN},
    [BATADV_ATTR_TT_TTVN] = {.type = NLA_U8},
    [BATADV_ATTR_TT_LAST_TTVN] = {.type = NLA_U8},
    [BATADV_ATTR_TT_CRC32] = {.type = NLA_U32},
    [BATADV_ATTR_TT_VID] = {.type = NLA_U16},
    [BATADV_ATTR_TT_FLAGS] = {.type = NLA_U32},
    [BATADV_ATTR_FLAG_BEST] = {.type = NLA_FLAG},
    [BATADV_ATTR_LAST_SEEN_MSECS] = {.type = NLA_U32},
    [BATADV_ATTR_NEIGH_ADDRESS] = {.type = NLA_UNSPEC,
                                   .minlen = ETH_ALEN,
                                   .maxlen = ETH_ALEN},
    [BATADV_ATTR_TQ] = {.type = NLA_U8},
    [BATADV_ATTR_THROUGHPUT] = {.type = NLA_U32},
    [BATADV_ATTR_BANDWIDTH_UP] = {.type = NLA_U32},
    [BATADV_ATTR_BANDWIDTH_DOWN] = {.type = NLA_U32},
    [BATADV_ATTR_ROUTER] = {.type = NLA_UNSPEC,
                            .minlen = ETH_ALEN,
                            .maxlen = ETH_ALEN},
    [BATADV_ATTR_BLA_OWN] = {.type = NLA_FLAG},
    [BATADV_ATTR_BLA_ADDRESS] = {.type = NLA_UNSPEC,
                                 .minlen = ETH_ALEN,
                                 .maxlen = ETH_ALEN},
    [BATADV_ATTR_BLA_VID] = {.type = NLA_U16},
    [BATADV_ATTR_BLA_BACKBONE] = {.type = NLA_UNSPEC,
                                  .minlen = ETH_ALEN,
                                  .maxlen = ETH_ALEN},
    [BATADV_ATTR_BLA_CRC] = {.type = NLA_U16},
    [BATADV_ATTR_DAT_CACHE_IP4ADDRESS] = {.type = NLA_U32},
    [BATADV_ATTR_DAT_CACHE_HWADDRESS] = {.type = NLA_UNSPEC,
                                         .minlen = ETH_ALEN,
                                         .maxlen = ETH_ALEN},
    [BATADV_ATTR_DAT_CACHE_VID] = {.type = NLA_U16},
    [BATADV_ATTR_MCAST_FLAGS] = {.type = NLA_U32},
    [BATADV_ATTR_MCAST_FLAGS_PRIV] = {.type = NLA_U32},
    [BATADV_ATTR_VLANID] = {.type = NLA_U16},
    [BATADV_ATTR_AGGREGATED_OGMS_ENABLED] = {.type = NLA_U8},
    [BATADV_ATTR_AP_ISOLATION_ENABLED] = {.type = NLA_U8},
    [BATADV_ATTR_ISOLATION_MARK] = {.type = NLA_U32},
    [BATADV_ATTR_ISOLATION_MASK] = {.type = NLA_U32},
    [BATADV_ATTR_BONDING_ENABLED] = {.type = NLA_U8},
    [BATADV_ATTR_BRIDGE_LOOP_AVOIDANCE_ENABLED] = {.type = NLA_U8},
    [BATADV_ATTR_DISTRIBUTED_ARP_TABLE_ENABLED] = {.type = NLA_U8},
    [BATADV_ATTR_FRAGMENTATION_ENABLED] = {.type = NLA_U8},
    [BATADV_ATTR_GW_BANDWIDTH_DOWN] = {.type = NLA_U32},
    [BATADV_ATTR_GW_BANDWIDTH_UP] = {.type = NLA_U32},
    [BATADV_ATTR_GW_MODE] = {.type = NLA_U8},
    [BATADV_ATTR_GW_SEL_CLASS] = {.type = NLA_U32},
    [BATADV_ATTR_HOP_PENALTY] = {.type = NLA_U8},
    [BATADV_ATTR_LOG_LEVEL] = {.type = NLA_U32},
    [BATADV_ATTR_MULTICAST_FORCEFLOOD_ENABLED] = {.type = NLA_U8},
    [BATADV_ATTR_MULTICAST_FANOUT] = {.type = NLA_U32},
    [BATADV_ATTR_NETWORK_CODING_ENABLED] = {.type = NLA_U8},
    [BATADV_ATTR_ORIG_INTERVAL] = {.type = NLA_U32},
    [BATADV_ATTR_ELP_INTERVAL] = {.type = NLA_U32},
    [BATADV_ATTR_THROUGHPUT_OVERRIDE] = {.type = NLA_U32},
};

/**
 * Options that are passed to the tq_callback function
 */
struct opts {
    char* file_name;
    int mode;
};

/**
 * What to do when an error occurs during communcation
 * Copied from netlink.c
 */
int netlink_print_error(struct sockaddr_nl* nla __maybe_unused,
                        struct nlmsgerr* nlerr, void* arg __maybe_unused) {
    if (nlerr->error != -95)
        fprintf(stderr, "Error received: %s\n", strerror(-nlerr->error));

    return NL_STOP;
}

/**
 * What to do when communications are stopped (idk when this happens)
 * Copied from netlink.c
 */
int netlink_stop_callback(struct nl_msg* msg, void* arg __maybe_unused) {
    struct nlmsghdr* nlh = nlmsg_hdr(msg);
    int* error = nlmsg_data(nlh);

    if (*error) fprintf(stderr, "Error received: %s\n", strerror(-*error));

    return NL_STOP;
}

/**
 * Convert a MAC address in a uint8_t array to a string
 */
void mac_to_str(char* mac_str, uint8_t* mac) {
    sprintf(mac_str, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3],
            mac[4], mac[5]);
}

/**
 * Save TQ data to csv file
 * Data is formatted as MAC,TQ,DATE
 */
void save_tq(char* file_name, uint8_t* mac, int tq, char* recv_time) {
    char mac_str[18];
    mac_to_str(mac_str, mac);

    FILE* out;
    out = fopen(file_name, "a");
    fprintf(out, "%s,%d,%s\n", mac_str, tq, recv_time);
    fclose(out);
}

/**
 * Process data received from kernel
 * Based on originators_callback in originators.c
 */
static int tq_callback(struct nl_msg* msg, void* arg) {
    struct nlattr* attrs[61];
    struct nlmsghdr* nlh = nlmsg_hdr(msg);
    struct genlmsghdr* ghdr;

    struct opts* options = arg;

    // Validate header
    if (!genlmsg_valid_hdr(nlh, 0)) {
        fputs("Received invalid data from kernel.\n", stderr);
        exit(5);
    }

    // Parse data into attrs array
    ghdr = nlmsg_data(nlh);
    if (nla_parse(attrs, 60, genlmsg_attrdata(ghdr, 0), genlmsg_len(ghdr),
                  batadv_netlink_policy)) {
        fputs("Received invalid data from kernel.\n", stderr);
        exit(5);
    }

    // Process data
    uint8_t* orig = nla_data(attrs[BATADV_ATTR_ORIG_ADDRESS]);
    uint8_t* neigh = nla_data(attrs[BATADV_ATTR_NEIGH_ADDRESS]);
    int tq = nla_get_u8(attrs[BATADV_ATTR_TQ]);

    // Filter out multi-hop OGMs
    if (orig[0] != neigh[0] || orig[1] != neigh[1] || orig[2] != neigh[2] ||
        orig[3] != neigh[3] || orig[4] != neigh[4] || orig[5] != neigh[5])
        return NL_OK;

    // Get current time
    time_t now;
    time(&now);
    char* recv_time = ctime(&now);
    recv_time[24] = 0;  // Remove newline

    // Save data to file
    save_tq(options->file_name, orig, tq, recv_time);

    return NL_OK;
}

int main(int argc, char** argv) {
    float wait = 1;
    int repetitions = 5;
    char* file_name = malloc(13 * sizeof(char));
    strcpy(file_name, "./tqdata.csv");

    // Parse arguments

    int optchar;
    while ((optchar = getopt(argc, argv, "+cf:r:w:")) != -1) {
        switch (optchar) {
            case 'c':
                repetitions = -1;
                break;
            case 'f':
                free(file_name);
                file_name = malloc((strlen(optarg) + 1) * sizeof(char));
                strcpy(file_name, optarg);
                break;
            case 'r':
                if (!sscanf(optarg, "%d", &repetitions)) {
                    fprintf(
                        stderr,
                        "Error - provided argument of '-%c' is not a number\n",
                        optchar);
                    return 1;
                }
                break;
            case 'w':
                if (!sscanf(optarg, "%f", &wait)) {
                    fprintf(
                        stderr,
                        "Error - provided argument of '-%c' is not a number\n",
                        optchar);
                    return 1;
                }
                break;
            default:
                fprintf(stderr, "Error - '-%c' not recognized\n", optchar);
                return 1;
        }
    }

    struct opts options = {
        .file_name = file_name,
        .mode = 0,
    };

    // Clear output file and add header

    FILE* out;
    out = fopen(options.file_name, "w");
    fprintf(out, "%s,%s,%s\n", "MAC", "TQ", "TIME");
    fclose(out);

    // Prepare for communication

    /// Based on functions.c - check_mesh_iface
    unsigned int mesh_ifindex = if_nametoindex("bat0");

    /// Based on/copied from netlink.c - netlink_create
    struct nl_sock* sock = nl_socket_alloc();
    if (!sock) return 2;
    genl_connect(sock);

    /// Based on netlink.c - netlink_create
    struct nl_cb* cb = nl_cb_alloc(NL_CB_DEFAULT);
    if (!cb) return 3;

    /// Based on netlink.c - netlink_create
    int batadv_family = genl_ctrl_resolve(sock, "batadv");

    // Set up callbacks for receiving data

    struct nl_msg* msg;

    /// Based on/copied from netlink.c - netlink_print_common
    nl_cb_set(cb, NL_CB_VALID, NL_CB_CUSTOM, tq_callback, &options);
    nl_cb_set(cb, NL_CB_FINISH, NL_CB_CUSTOM, netlink_stop_callback, NULL);
    nl_cb_err(cb, NL_CB_CUSTOM, netlink_print_error, NULL);

    // Ask kernel for data (data is processed in the callback)

    unsigned int i = 0;  // Assumption: this program will not be run for over 4.3 billion iterations
    
    /// Based on netlink.c - netlink_print_common
    while (repetitions == -1 || i < repetitions) {
        msg = nlmsg_alloc();
        if (!msg) return 4;
        genlmsg_put(msg, NL_AUTO_PID, NL_AUTO_SEQ, batadv_family, 0, NLM_F_DUMP,
                    8, 1);
        nla_put_u32(msg, 3, mesh_ifindex);
        nl_send_auto_complete(sock, msg);
        nlmsg_free(msg);
        nl_recvmsgs(sock, cb);
        usleep(1000000 * wait);
        i++;
    }

    free(file_name);

    return 0;
}
