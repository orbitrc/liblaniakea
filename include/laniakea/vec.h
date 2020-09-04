#ifndef _LANIAKEA_VEC_H
#define _LANIAKEA_VEC_H

#include <stdlib.h>

#include <laniakea/base.h>

#define LANIAKEA_VEC_CAPACITY_MULTIPLE 4

LANIAKEA_EXTERN_C_BEGIN

typedef struct laniakea_string_vec {
    size_t length;
    size_t capacity;
    char **strings;
} laniakea_string_vec;

/*=============================*/
/* laniakea_string_vec methods */
/*=============================*/

laniakea_string_vec* laniakea_string_vec_new();
void laniakea_string_vec_push(laniakea_string_vec *vec, const char *str);
const char* laniakea_string_vec_get(laniakea_string_vec *vec, size_t index);
void laniakea_string_vec_free(laniakea_string_vec *vec);

LANIAKEA_EXTERN_C_END

#endif /* _LANIAKEA_VEC_H */