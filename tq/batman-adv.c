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

#include "batman-adv.h"

/**
 * Format of a batman-adv message received from netlink
 * 
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
