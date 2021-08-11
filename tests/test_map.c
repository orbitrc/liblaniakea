#include <assert.h>
#include <stdio.h>

#include <laniakea/map.h>

void test_replace()
{
    la_string_map *map = la_string_map_new();

    la_string_map_insert(map, "one", "하나");
    la_string_map_insert(map, "two", "두울");
    la_string_map_insert(map, "three", "셋");
    la_string_map_insert(map, "four", "넷");
    la_string_map_insert(map, "five", "다섯");

    la_string_map_insert(map, "two", "둘");

    printf("two: %s\n", la_string_map_get(map, "two"));

    la_string_map_free(map);
}

void test_remove()
{
    la_string_map *map = la_string_map_new();

    la_string_map_insert(map, "1", "foo");
    la_string_map_insert(map, "2", "bar");
    la_string_map_insert(map, "3", "baz");
    la_string_map_insert(map, "4", "qux");

    // Remove.
    la_string_map_remove(map, "2");

    la_string_map_insert(map, "5", "barr");

    for (size_t i = 0; i < map->length; ++i) {
        printf("%s: %s\n", map->pairs[i]->key, map->pairs[i]->value);
    }
    assert(map->length == 4);

    la_string_map_free(map);
}

int main()
{
    la_string_map *map = la_string_map_new();

    la_string_map_insert(map, "foo", "bar");
    la_string_map_insert(map, "one", "1");
    la_string_map_insert(map, "two", "2");
    printf("capacity: %ld\n", map->capacity);
    la_string_map_insert(map, "three", "3");
    printf("capacity: %ld\n", map->capacity);
    la_string_map_insert(map, "four", "4");

    const char *val = la_string_map_get(map, "two");
    printf("\"two\": %s\n", val);

    // Replace test.
    la_string_map_insert(map, "foo", "Hello!");
    val = la_string_map_get(map, "foo");
    printf("\"%s\"\n", val);
    printf("length: %ld\n", map->length);

    la_string_map_free(map);

    printf("\n");

    printf("test replace.\n");
    printf("==============\n");
    test_replace();

    printf("\n");

    printf("test_remove\n");
    printf("=============\n");
    test_remove();

    return 0;
}
