#include <laniakea/vec.h>

#include <string.h>

LA_EXTERN_C_BEGIN

la_string_vec* la_string_vec_new()
{
    la_string_vec *vec = malloc(sizeof(la_string_vec));

    vec->length = 0;
    vec->capacity = LA_VEC_CAPACITY_MULTIPLE;
    vec->strings = malloc(sizeof(char*) * vec->capacity);

    return vec;
}

void la_string_vec_push(la_string_vec *vec, const char *str)
{
    vec->strings[vec->length] = malloc(sizeof(char) * strlen(str) + 1);
    strcpy(vec->strings[vec->length], str);
    vec->length++;

    if (vec->length == vec->capacity) {
        char **new_strings = malloc(
            sizeof(char*)
                *
            (vec->capacity + LA_VEC_CAPACITY_MULTIPLE)
        );

        for (size_t i = 0; i < vec->length; ++i) {
            new_strings[i] = malloc(strlen(vec->strings[i]) + 1);
            strcpy(new_strings[i], vec->strings[i]);
            free(vec->strings[i]);
        }
        free(vec->strings);
        vec->strings = new_strings;

        vec->capacity += LA_VEC_CAPACITY_MULTIPLE;
    }
}

const char* la_string_vec_get(la_string_vec *vec, size_t index)
{
    return vec->strings[index];
}

void la_string_vec_free(la_string_vec *vec)
{
    for (size_t i = 0; i < vec->length; ++i) {
        free(vec->strings[i]);
    }

    free(vec);
}

LA_EXTERN_C_END
