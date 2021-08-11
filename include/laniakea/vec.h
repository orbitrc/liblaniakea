#ifndef _LANIAKEA_VEC_H
#define _LANIAKEA_VEC_H

#include <stdlib.h>

#include <laniakea/base.h>

#define LA_VEC_CAPACITY_MULTIPLE 4

LA_EXTERN_C_BEGIN

typedef struct la_string_vec {
    size_t length;
    size_t capacity;
    char **strings;
} la_string_vec;

/*=======================*/
/* la_string_vec methods */
/*=======================*/

la_string_vec* la_string_vec_new();
void la_string_vec_push(la_string_vec *vec, const char *str);
const char* la_string_vec_get(la_string_vec *vec, size_t index);
void la_string_vec_free(la_string_vec *vec);

LA_EXTERN_C_END

#endif /* _LANIAKEA_VEC_H */
