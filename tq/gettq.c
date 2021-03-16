#include "gettq.h"

int main(int argc, char** argv) {
    if (argc < 2) throw_error(ARGUMENT_ERR, "MAC address is required");
    int mac_len = strlen(argv[1]);
    if (mac_len > 12) throw_error(ARGUMENT_ERR, "Invalid MAC address %s: too long\nPlease do not use any colons\n", argv[1]);
    else if (mac_len < 12) throw_error(ARGUMENT_ERR, "Invalid MAC address %s: too short\n", argv[1]);

    // Print one TQ for $mac to stdout
    struct opts options = {
        .mode = PRINT,
        .repetitions = 1,
        .mac = argv[1],
    };

    netlink_comm_loop(&options);

    return 0;
}
