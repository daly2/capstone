#ifndef TQ_UTIL_H
#define TQ_UTIL_H

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum error_code {
    ARGUMENT_ERR = 1,
    FILE_ERR,
    NL_ALLOC_ERR,
    NL_PARSE_ERR,
};

enum program_mode { LOG, PRINT };

/**
 * Options that are passed to the tq_callback function
 */
struct opts {
    enum program_mode mode;
    char* file_name;
    int repetitions;
    float wait;
    char* mac;
};

void mac_to_str(char* mac_str, uint8_t* mac);

void save_tq(char* file_name, uint8_t* mac, int tq, char* recv_time);

enum open_mode { WRITE, APPEND };

void save_line_to_file(char* file_name, char* mac, char* tq, char* recv_time,
                       enum open_mode open_mode);

void throw_error(enum error_code code, const char* message, ...) __THROW
    __attribute__((__noreturn__));

#endif  // TQ_UTIL_H
