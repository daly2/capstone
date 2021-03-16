#ifndef TQ_NETLINK_H
#define TQ_NETLINK_H

#include <net/if.h>
#include <netlink/genl/ctrl.h>
#include <netlink/genl/genl.h>
#include <netlink/msg.h>
#include <netlink/netlink.h>
#include <netlink/types.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "batman-adv.h"
#include "util.h"

/**
 * What to do when an error occurs during communcation
 * Copied from netlink.c
 */
int netlink_print_error(struct sockaddr_nl* nla __maybe_unused,
                        struct nlmsgerr* nlerr, void* arg __maybe_unused);

/**
 * What to do when communications are stopped (idk when this happens)
 * Copied from netlink.c
 */
int netlink_stop_callback(struct nl_msg* msg, void* arg __maybe_unused);

/**
 * Process data received from kernel
 * Based on originators_callback in originators.c
 */
int tq_callback(struct nl_msg* msg, void* arg);

void netlink_comm_loop(struct opts* options);

#endif  // TQ_NETLINK_H
