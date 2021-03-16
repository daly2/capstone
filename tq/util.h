#ifndef TQ_UTIL_H
#define TQ_UTIL_H

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Indicate what the error is rather than using an arbitrary number
 */
enum error_code {
    ARGUMENT_ERR = 1,
    FILE_ERR,
    NL_ALLOC_ERR,
    NL_PARSE_ERR,
    UNDEFINED_BEHAVIOR_ERR,
};

/**
 * Indicates how the program should work
 */
enum program_mode {
    /**
     * Log TQ data for all neighboring nodes to a file
     */
    LOG,
    /**
     * Find the TQ for a single neighbor and print it to stdout
     */
    PRINT
};

/**
 * Options that control how the program works
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

/**
 * Controls how a file will be opened
 */
enum open_mode { WRITE, APPEND };

void save_line_to_file(char* file_name, char* mac, char* tq, char* recv_time,
                       enum open_mode open_mode);

void throw_error(enum error_code code, const char* message, ...) __THROW
    __attribute__((__noreturn__));

#endif  // TQ_UTIL_H
