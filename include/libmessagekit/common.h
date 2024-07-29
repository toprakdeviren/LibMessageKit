#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    ERROR_NONE = 0,
    ERROR_NETWORK,
    ERROR_INVALID_PARAMS,
    ERROR_DATABASE,
    ERROR_UNAUTHORIZED,
    ERROR_UNKNOWN,
    ERROR_ALREADY_INITIALIZED,
    ERROR_INVALID_PARAMETERS,
    ERROR_DATABASE_INITIALIZATION,
    ERROR_MEMORY_ALLOCATION,
    ERROR_SCHEMA_INITIALIZATION,
    ERROR_INVALID_STORAGE_PATH,
    ERROR_INVALID_DATABASE_FILENAME
} ErrorCode;

#endif //COMMON_H
