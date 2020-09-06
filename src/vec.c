#include <laniakea/vec.h>

#include <string.h>

LANIAKEA_EXTERN_C_BEGIN

laniakea_string_vec* laniakea_string_vec_new()
{
    laniakea_string_vec *vec = malloc(sizeof(laniakea_string_vec));

    vec->length = 0;
    vec->capacity = LANIAKEA_VEC_CAPACITY_MULTIPLE;
    vec->strings = malloc(sizeof(char*) * vec->capacity);

    return vec;
}

void laniakea_string_vec_push(laniakea_string_vec *vec, const char *str)
{
    vec->strings[vec->length] = malloc(sizeof(char) * strlen(str));
    strcpy(vec->strings[vec->length], str);
    vec->length++;

    if (vec->length == vec->capacity) {
        char **new_strings = malloc(
            sizeof(char*)
                *
            vec->capacity + LANIAKEA_VEC_CAPACITY_MULTIPLE
        );

        for (size_t i = 0; i < vec->length; ++i) {
            new_strings[i] = vec->strings[i];
        }
        free(vec->strings);
        vec->strings = new_strings;

        vec->capacity += LANIAKEA_VEC_CAPACITY_MULTIPLE;
    }
}

const char* laniakea_string_vec_get(laniakea_string_vec *vec, size_t index)
{
    return vec->strings[index];
}

void laniakea_string_vec_free(laniakea_string_vec *vec)
{
    for (size_t i = 0; i < vec->length; ++i) {
        free(vec->strings[i]);
    }

    free(vec);
}

LANIAKEA_EXTERN_C_END