#include <stdio.h>

#include <laniakea/vec.h>

int main()
{
    la_string_vec *vec = la_string_vec_new();

    la_string_vec_push(vec, "Hello");
    la_string_vec_push(vec, ",");
    la_string_vec_push(vec, "world");
    la_string_vec_push(vec, "!");
    la_string_vec_push(vec, "foo");
    la_string_vec_push(vec, "bar");
    la_string_vec_push(vec, "baz");
    printf("vec capacity: %ld\n", vec->capacity);
    printf("vec length: %ld\n", vec->length);

    for (size_t i = 0; i < vec->length; ++i) {
        printf("%s\n", la_string_vec_get(vec, i));
    }

    return 0;
}
