#include <stdio.h>

#include <laniakea/vec.h>

int main()
{
    laniakea_string_vec *vec = laniakea_string_vec_new();

    laniakea_string_vec_push(vec, "Hello");
    laniakea_string_vec_push(vec, ",");
    laniakea_string_vec_push(vec, "world");
    laniakea_string_vec_push(vec, "!");
    laniakea_string_vec_push(vec, "foo");
    laniakea_string_vec_push(vec, "bar");
    laniakea_string_vec_push(vec, "baz");
    printf("vec length: %ld\n", vec->length);

    for (size_t i = 0; i < vec->length; ++i) {
        printf("%s\n", laniakea_string_vec_get(vec, i));
    }
    
    return 0;
}