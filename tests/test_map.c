#include <assert.h>
#include <stdio.h>

#include <laniakea/map.h>

void test_replace()
{
    laniakea_string_map *map = laniakea_string_map_new();

    laniakea_string_map_insert(map, "one", "하나");
    laniakea_string_map_insert(map, "two", "두울");
    laniakea_string_map_insert(map, "three", "셋");

    laniakea_string_map_insert(map, "two", "둘");

    printf("two: %s\n", laniakea_string_map_get(map, "two"));

    laniakea_string_map_free(map);
}

void test_remove()
{
    laniakea_string_map *map = laniakea_string_map_new();

    laniakea_string_map_insert(map, "1", "foo");
    laniakea_string_map_insert(map, "2", "bar");
    laniakea_string_map_insert(map, "3", "baz");

    // Remove.
    laniakea_string_map_remove(map, "2");

    laniakea_string_map_insert(map, "4", "barr");

    for (size_t i = 0; i < map->length; ++i) {
        printf("%s: %s\n", map->pairs[i]->key, map->pairs[i]->value);
    }
    assert(map->length == 3);

    laniakea_string_map_free(map);
}

int main()
{
    laniakea_string_map *map = laniakea_string_map_new();

    laniakea_string_map_insert(map, "foo", "bar");
    laniakea_string_map_insert(map, "one", "1");
    laniakea_string_map_insert(map, "two", "2");
    printf("capacity: %ld\n", map->capacity);
    laniakea_string_map_insert(map, "three", "3");
    printf("capacity: %ld\n", map->capacity);
    laniakea_string_map_insert(map, "four", "4");

    const char *val = laniakea_string_map_get(map, "two");
    printf("\"two\": %s\n", val);

    // Replace test.
    laniakea_string_map_insert(map, "foo", "Hello!");
    val = laniakea_string_map_get(map, "foo");
    printf("\"%s\"\n", val);
    printf("length: %ld\n", map->length);

    laniakea_string_map_free(map);

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
