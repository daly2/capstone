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

#ifndef TQ_BATMAN_ADV_H
#define TQ_BATMAN_ADV_H

#include <net/ethernet.h>
#include <netlink/msg.h>
#include <netlink/netlink.h>

/**
 * Tracks which indices correspond to which data points in a batman-adv message
 * Copied from batman_adv.c
 */
enum batadv_nl_attrs {
    /**
     * @BATADV_ATTR_UNSPEC: unspecified attribute to catch errors
     */
    BATADV_ATTR_UNSPEC,

    /**
     * @BATADV_ATTR_VERSION: batman-adv version string
     */
    BATADV_ATTR_VERSION,

    /**
     * @BATADV_ATTR_ALGO_NAME: name of routing algorithm
     */
    BATADV_ATTR_ALGO_NAME,

    /**
     * @BATADV_ATTR_MESH_IFINDEX: index of the batman-adv interface
     */
    BATADV_ATTR_MESH_IFINDEX,

    /**
     * @BATADV_ATTR_MESH_IFNAME: name of the batman-adv interface
     */
    BATADV_ATTR_MESH_IFNAME,

    /**
     * @BATADV_ATTR_MESH_ADDRESS: mac address of the batman-adv interface
     */
    BATADV_ATTR_MESH_ADDRESS,

    /**
     * @BATADV_ATTR_HARD_IFINDEX: index of the non-batman-adv interface
     */
    BATADV_ATTR_HARD_IFINDEX,

    /**
     * @BATADV_ATTR_HARD_IFNAME: name of the non-batman-adv interface
     */
    BATADV_ATTR_HARD_IFNAME,

    /**
     * @BATADV_ATTR_HARD_ADDRESS: mac address of the non-batman-adv
     * interface
     */
    BATADV_ATTR_HARD_ADDRESS,

    /**
     * @BATADV_ATTR_ORIG_ADDRESS: originator mac address
     */
    BATADV_ATTR_ORIG_ADDRESS,

    /**
     * @BATADV_ATTR_TPMETER_RESULT: result of run (see
     * batadv_tp_meter_status)
     */
    BATADV_ATTR_TPMETER_RESULT,

    /**
     * @BATADV_ATTR_TPMETER_TEST_TIME: time (msec) the run took
     */
    BATADV_ATTR_TPMETER_TEST_TIME,

    /**
     * @BATADV_ATTR_TPMETER_BYTES: amount of acked bytes during run
     */
    BATADV_ATTR_TPMETER_BYTES,

    /**
     * @BATADV_ATTR_TPMETER_COOKIE: session cookie to match tp_meter session
     */
    BATADV_ATTR_TPMETER_COOKIE,

    /**
     * @BATADV_ATTR_PAD: attribute used for padding for 64-bit alignment
     */
    BATADV_ATTR_PAD,

    /**
     * @BATADV_ATTR_ACTIVE: Flag indicating if the hard interface is active
     */
    BATADV_ATTR_ACTIVE,

    /**
     * @BATADV_ATTR_TT_ADDRESS: Client MAC address
     */
    BATADV_ATTR_TT_ADDRESS,

    /**
     * @BATADV_ATTR_TT_TTVN: Translation table version
     */
    BATADV_ATTR_TT_TTVN,

    /**
     * @BATADV_ATTR_TT_LAST_TTVN: Previous translation table version
     */
    BATADV_ATTR_TT_LAST_TTVN,

    /**
     * @BATADV_ATTR_TT_CRC32: CRC32 over translation table
     */
    BATADV_ATTR_TT_CRC32,

    /**
     * @BATADV_ATTR_TT_VID: VLAN ID
     */
    BATADV_ATTR_TT_VID,

    /**
     * @BATADV_ATTR_TT_FLAGS: Translation table client flags
     */
    BATADV_ATTR_TT_FLAGS,

    /**
     * @BATADV_ATTR_FLAG_BEST: Flags indicating entry is the best
     */
    BATADV_ATTR_FLAG_BEST,

    /**
     * @BATADV_ATTR_LAST_SEEN_MSECS: Time in milliseconds since last seen
     */
    BATADV_ATTR_LAST_SEEN_MSECS,

    /**
     * @BATADV_ATTR_NEIGH_ADDRESS: Neighbour MAC address
     */
    BATADV_ATTR_NEIGH_ADDRESS,

    /**
     * @BATADV_ATTR_TQ: TQ to neighbour
     */
    BATADV_ATTR_TQ,

    /**
     * @BATADV_ATTR_THROUGHPUT: Estimated throughput to Neighbour
     */
    BATADV_ATTR_THROUGHPUT,

    /**
     * @BATADV_ATTR_BANDWIDTH_UP: Reported uplink bandwidth
     */
    BATADV_ATTR_BANDWIDTH_UP,

    /**
     * @BATADV_ATTR_BANDWIDTH_DOWN: Reported downlink bandwidth
     */
    BATADV_ATTR_BANDWIDTH_DOWN,

    /**
     * @BATADV_ATTR_ROUTER: Gateway router MAC address
     */
    BATADV_ATTR_ROUTER,

    /**
     * @BATADV_ATTR_BLA_OWN: Flag indicating own originator
     */
    BATADV_ATTR_BLA_OWN,

    /**
     * @BATADV_ATTR_BLA_ADDRESS: Bridge loop avoidance claim MAC address
     */
    BATADV_ATTR_BLA_ADDRESS,

    /**
     * @BATADV_ATTR_BLA_VID: BLA VLAN ID
     */
    BATADV_ATTR_BLA_VID,

    /**
     * @BATADV_ATTR_BLA_BACKBONE: BLA gateway originator MAC address
     */
    BATADV_ATTR_BLA_BACKBONE,

    /**
     * @BATADV_ATTR_BLA_CRC: BLA CRC
     */
    BATADV_ATTR_BLA_CRC,

    /**
     * @BATADV_ATTR_DAT_CACHE_IP4ADDRESS: Client IPv4 address
     */
    BATADV_ATTR_DAT_CACHE_IP4ADDRESS,

    /**
     * @BATADV_ATTR_DAT_CACHE_HWADDRESS: Client MAC address
     */
    BATADV_ATTR_DAT_CACHE_HWADDRESS,

    /**
     * @BATADV_ATTR_DAT_CACHE_VID: VLAN ID
     */
    BATADV_ATTR_DAT_CACHE_VID,

    /**
     * @BATADV_ATTR_MCAST_FLAGS: Per originator multicast flags
     */
    BATADV_ATTR_MCAST_FLAGS,

    /**
     * @BATADV_ATTR_MCAST_FLAGS_PRIV: Private, own multicast flags
     */
    BATADV_ATTR_MCAST_FLAGS_PRIV,

    /**
     * @BATADV_ATTR_VLANID: VLAN id on top of soft interface
     */
    BATADV_ATTR_VLANID,

    /**
     * @BATADV_ATTR_AGGREGATED_OGMS_ENABLED: whether the batman protocol
     *  messages of the mesh interface shall be aggregated or not.
     */
    BATADV_ATTR_AGGREGATED_OGMS_ENABLED,

    /**
     * @BATADV_ATTR_AP_ISOLATION_ENABLED: whether the data traffic going
     *  from a wireless client to another wireless client will be silently
     *  dropped.
     */
    BATADV_ATTR_AP_ISOLATION_ENABLED,

    /**
     * @BATADV_ATTR_ISOLATION_MARK: the isolation mark which is used to
     *  classify clients as "isolated" by the Extended Isolation feature.
     */
    BATADV_ATTR_ISOLATION_MARK,

    /**
     * @BATADV_ATTR_ISOLATION_MASK: the isolation (bit)mask which is used to
     *  classify clients as "isolated" by the Extended Isolation feature.
     */
    BATADV_ATTR_ISOLATION_MASK,

    /**
     * @BATADV_ATTR_BONDING_ENABLED: whether the data traffic going through
     *  the mesh will be sent using multiple interfaces at the same time.
     */
    BATADV_ATTR_BONDING_ENABLED,

    /**
     * @BATADV_ATTR_BRIDGE_LOOP_AVOIDANCE_ENABLED: whether the bridge loop
     *  avoidance feature is enabled. This feature detects and avoids loops
     *  between the mesh and devices bridged with the soft interface
     */
    BATADV_ATTR_BRIDGE_LOOP_AVOIDANCE_ENABLED,

    /**
     * @BATADV_ATTR_DISTRIBUTED_ARP_TABLE_ENABLED: whether the distributed
     *  arp table feature is enabled. This feature uses a distributed hash
     *  table to answer ARP requests without flooding the request through
     *  the whole mesh.
     */
    BATADV_ATTR_DISTRIBUTED_ARP_TABLE_ENABLED,

    /**
     * @BATADV_ATTR_FRAGMENTATION_ENABLED: whether the data traffic going
     *  through the mesh will be fragmented or silently discarded if the
     *  packet size exceeds the outgoing interface MTU.
     */
    BATADV_ATTR_FRAGMENTATION_ENABLED,

    /**
     * @BATADV_ATTR_GW_BANDWIDTH_DOWN: defines the download bandwidth which
     *  is propagated by this node if %BATADV_ATTR_GW_BANDWIDTH_MODE was set
     *  to 'server'.
     */
    BATADV_ATTR_GW_BANDWIDTH_DOWN,

    /**
     * @BATADV_ATTR_GW_BANDWIDTH_UP: defines the upload bandwidth which
     *  is propagated by this node if %BATADV_ATTR_GW_BANDWIDTH_MODE was set
     *  to 'server'.
     */
    BATADV_ATTR_GW_BANDWIDTH_UP,

    /**
     * @BATADV_ATTR_GW_MODE: defines the state of the gateway features.
     * Possible values are specified in enum batadv_gw_modes
     */
    BATADV_ATTR_GW_MODE,

    /**
     * @BATADV_ATTR_GW_SEL_CLASS: defines the selection criteria this node
     *  will use to choose a gateway if gw_mode was set to 'client'.
     */
    BATADV_ATTR_GW_SEL_CLASS,

    /**
     * @BATADV_ATTR_HOP_PENALTY: defines the penalty which will be applied
     *  to an originator message's tq-field on every hop and/or per
     *  hard interface
     */
    BATADV_ATTR_HOP_PENALTY,

    /**
     * @BATADV_ATTR_LOG_LEVEL: bitmask with to define which debug messages
     *  should be send to the debug log/trace ring buffer
     */
    BATADV_ATTR_LOG_LEVEL,

    /**
     * @BATADV_ATTR_MULTICAST_FORCEFLOOD_ENABLED: whether multicast
     *  optimizations should be replaced by simple broadcast-like flooding
     *  of multicast packets. If set to non-zero then all nodes in the mesh
     *  are going to use classic flooding for any multicast packet with no
     *  optimizations.
     */
    BATADV_ATTR_MULTICAST_FORCEFLOOD_ENABLED,

    /**
     * @BATADV_ATTR_NETWORK_CODING_ENABLED: whether Network Coding (using
     *  some magic to send fewer wifi packets but still the same content) is
     *  enabled or not.
     */
    BATADV_ATTR_NETWORK_CODING_ENABLED,

    /**
     * @BATADV_ATTR_ORIG_INTERVAL: defines the interval in milliseconds in
     *  which batman sends its protocol messages.
     */
    BATADV_ATTR_ORIG_INTERVAL,

    /**
     * @BATADV_ATTR_ELP_INTERVAL: defines the interval in milliseconds in
     *  which batman emits probing packets for neighbor sensing (ELP).
     */
    BATADV_ATTR_ELP_INTERVAL,

    /**
     * @BATADV_ATTR_THROUGHPUT_OVERRIDE: defines the throughput value to be
     *  used by B.A.T.M.A.N. V when estimating the link throughput using
     *  this interface. If the value is set to 0 then batman-adv will try to
     *  estimate the throughput by itself.
     */
    BATADV_ATTR_THROUGHPUT_OVERRIDE,

    /**
     * @BATADV_ATTR_MULTICAST_FANOUT: defines the maximum number of packet
     * copies that may be generated for a multicast-to-unicast conversion.
     * Once this limit is exceeded distribution will fall back to broadcast.
     */
    BATADV_ATTR_MULTICAST_FANOUT,

    /* add attributes above here, update the policy in netlink.c */

    /**
     * @__BATADV_ATTR_AFTER_LAST: internal use
     */
    __BATADV_ATTR_AFTER_LAST,

    /**
     * @NUM_BATADV_ATTR: total number of batadv_nl_attrs available
     */
    NUM_BATADV_ATTR = __BATADV_ATTR_AFTER_LAST,

    /**
     * @BATADV_ATTR_MAX: highest attribute number currently defined
     */
    BATADV_ATTR_MAX = __BATADV_ATTR_AFTER_LAST - 1
};

extern struct nla_policy batadv_netlink_policy[NUM_BATADV_ATTR];

/**
 * Used in batctl to indicate that an argument in a callback will always be null
 * Copied from main.h
 */
#define __maybe_unused __attribute__((unused))

#endif  // TQ_BATMAN_ADV_H
