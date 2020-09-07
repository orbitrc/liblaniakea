#ifndef _LANIAKEA_BASE_H
#define _LANIAKEA_BASE_H

#include <stdbool.h>

#ifdef __cplusplus
    #define LANIAKEA_EXTERN_C_BEGIN extern "C" {
#else
    #define LANIAKEA_EXTERN_C_BEGIN
#endif

#ifdef __cplusplus
    #define LANIAKEA_EXTERN_C_END }
#else
    #define LANIAKEA_EXTERN_C_END
#endif

#ifdef _Bool
#define laniakea_bool _Bool
#else
#define laniakea_bool bool
#endif
#define LANIAKEA_TRUE true
#define LANIAKEA_FALSE false

// File errors.
#define LANIAKEA_FILE_ERROR_SUCCESS         0
#define LANIAKEA_FILE_ERROR_NO_FILE         1
#define LANIAKEA_FILE_ERROR_PERMISSION      2
#define LANIAKEA_FILE_ERROR_NO_SPACE        3
#define LANIAKEA_FILE_ERROR_NO_DIRECTORY    4
#define LANIAKEA_FILE_ERROR_UNKNOWN         255

#endif /* _LANIAKEA_BASE_H */