#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    ERROR_NONE = 0,
    ERROR_NETWORK,
    ERROR_INVALID_PARAMS,
    ERROR_DATABASE,
    ERROR_UNAUTHORIZED,
    ERROR_UNKNOWN
} ErrorCode;

#endif //COMMON_H
