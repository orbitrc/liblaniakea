#include <stdio.h>

#include <laniakea/map.h>

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

    laniakea_string_map_free(map);

    return 0;
}
