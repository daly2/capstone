#include "util.h"

/**
 * Convert a MAC address in a uint8_t array to a string
 */
void mac_to_str(char* mac_str, uint8_t* mac) {
    sprintf(mac_str, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3],
            mac[4], mac[5]);
}
