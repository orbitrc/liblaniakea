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

#define laniakea_bool _Bool
#define LANIAKEA_TRUE true
#define LANIAKEA_FALSE false

#endif /* _LANIAKEA_BASE_H */