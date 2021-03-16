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

#include "gettq.h"

int main(int argc, char** argv) {
    struct opts options = {
        .mode = PRINT,
        .repetitions = 1,
        .mac = argv[1],
    };

    netlink_comm_loop(&options);

    return 0;
}
