#ifndef _LANIAKEA_BASE_H
#define _LANIAKEA_BASE_H

#include <stdbool.h>

#ifdef __cplusplus
    #define LA_EXTERN_C_BEGIN extern "C" {
#else
    #define LA_EXTERN_C_BEGIN
#endif

#ifdef __cplusplus
    #define LA_EXTERN_C_END }
#else
    #define LA_EXTERN_C_END
#endif

// File errors.
#define LA_FILE_ERROR_SUCCESS           0
#define LA_FILE_ERROR_NO_FILE           1
#define LA_FILE_ERROR_PERMISSION        2
#define LA_FILE_ERROR_NO_SPACE          3
#define LA_FILE_ERROR_NO_DIRECTORY      4
#define LA_FILE_ERROR_UNKNOWN           255

#endif /* _LANIAKEA_BASE_H */
