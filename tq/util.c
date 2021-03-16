#include "util.h"

/**
 * Convert a MAC address in a uint8_t array to a string
 */
void mac_to_str(char* mac_str, uint8_t* mac) {
    sprintf(mac_str, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3],
            mac[4], mac[5]);
}

/**
 * Save TQ data to csv file
 * 
 * Data is formatted as mac,tq,recv_time
 */
void save_tq(char* file_name, uint8_t* mac, int tq, char* recv_time) {
    char mac_str[18];
    mac_to_str(mac_str, mac);

    char tq_str[4];
    sprintf(tq_str, "%d", tq);

    save_line_to_file(file_name, mac_str, tq_str, recv_time, APPEND);
}

/**
 * Save line to csv file
 * 
 * Data is formatted as mac,tq,recv_time
 */
void save_line_to_file(char* file_name, char* mac, char* tq, char* recv_time, enum open_mode open_mode) {
    FILE* out;
    char mode_str[2];

    if (open_mode == WRITE) strcpy(mode_str, "w");
    else if (open_mode == APPEND) strcpy(mode_str, "a");
    else throw_error(FILE_ERR, "Bad open mode %d\n", open_mode);

    out = fopen(file_name, mode_str);
    if (!out) throw_error(FILE_ERR, "Error opening file %s\n", file_name);
    fprintf(out, "%s,%s,%s\n", mac, tq, recv_time);
    fclose(out);
}

/**
 * Print an error message and exit with code
 */
__THROW __attribute__ ((__noreturn__)) void throw_error(enum error_code code, const char* message_fmt, ...) {
    va_list args;
    va_start(args, message_fmt);
    vfprintf(stderr, message_fmt, args);
    va_end(args);

    exit(code);
}
