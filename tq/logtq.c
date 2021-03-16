#include "logtq.h"

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
                if (!sscanf(optarg, "%d", &repetitions))
                    throw_error(
                        ARGUMENT_ERR,
                        "Error - provided argument of '-%c' is not a number\n",
                        optchar);
                break;
            case 'w':
                if (!sscanf(optarg, "%f", &wait))
                    throw_error(
                        ARGUMENT_ERR,
                        "Error - provided argument of '-%c' is not a number\n",
                        optchar);
                break;
            default:
                throw_error(ARGUMENT_ERR, "Error - '-%c' not recognized\n",
                            optchar);
        }
    }

    // Log TQ values to $file_name every $wait seconds, $repetitions times
    struct opts options = {
        .mode = LOG,
        .file_name = file_name,
        .repetitions = repetitions,
        .wait = wait,
    };

    // Clear output file and add header
    save_line_to_file(options.file_name, "MAC", "TQ", "TIME", WRITE);

    netlink_comm_loop(&options);

    free(file_name);

    return 0;
}
