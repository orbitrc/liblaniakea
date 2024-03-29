#include <laniakea/map.h>

#include <string.h>

#include <laniakea/base.h>
#include <laniakea/string.h>

LA_EXTERN_C_BEGIN


/*==================================*/
/* la_string_map_pair methods */
/*==================================*/

la_string_map_pair* la_string_map_pair_new(const char *key,
        const char *value)
{
    la_string_map_pair *pair;
    // Initialize pair.
    pair = malloc(sizeof(la_string_map_pair));
    pair->key = NULL;
    pair->value = NULL;

    size_t key_len = strlen(key);
    size_t value_len = strlen(value);

    pair->key = malloc(key_len + 1);
    pair->value = malloc(value_len + 1);

    strncpy(pair->key, key, key_len);
    pair->key[key_len] = '\0';
    strncpy(pair->value, value, value_len);
    pair->value[value_len] = '\0';

    return pair;
}

void la_string_map_pair_free(la_string_map_pair *pair)
{
    if (pair->key != NULL) {
        free(pair->key);
    }
    if (pair->value != NULL) {
        free(pair->value);
    }
    free(pair);
}


/*=============================*/
/* la_string_map methods */
/*=============================*/

la_string_map* la_string_map_new()
{
    la_string_map *map;
    // Initialize map.
    map = malloc(sizeof(la_string_map));
    map->length = 0;
    map->capacity = LA_MAP_CAPACITY_MULTIPLE;
    map->pairs = malloc(sizeof(la_string_map_pair*)
        * LA_MAP_CAPACITY_MULTIPLE);

    return map;
}

bool la_string_map_contains(const la_string_map *map,
        const char *key)
{
    for (size_t i = 0; i < map->length; ++i) {
        if (la_string_eq(map->pairs[i]->key, key)) {
            return true;
        }
    }

    return false;
}

void la_string_map_insert(la_string_map *map,
        const char *key, const char *value)
{
    // If key already exists, replace.
    if (la_string_map_contains(map, key)) {
        la_string_map_remove(map, key);
        la_string_map_insert(map, key, value);

        return;
    }

    la_string_map_pair *pair = la_string_map_pair_new(key, value);
    map->pairs[map->length] = pair;
    map->length++;

    // If capacity is full, re-allocate more memory.
    if (map->length == map->capacity) {
        // Re-allocate more size.
        la_string_map_pair **new_pairs = malloc(
            sizeof(la_string_map_pair*)
                *
            (map->capacity + LA_MAP_CAPACITY_MULTIPLE)
        );
        // Copy pairs to new memory space.
        for (size_t i = 0; i < map->length; ++i) {
            new_pairs[i] = la_string_map_pair_new(
                map->pairs[i]->key, map->pairs[i]->value);
        }
        // Free old pairs.
        for (size_t i = 0; i < map->length; ++i) {
            la_string_map_pair_free(map->pairs[i]);
        }
        free(map->pairs);
        // Replace old pairs to new pairs.
        map->pairs = new_pairs;
        map->capacity += LA_MAP_CAPACITY_MULTIPLE;
    }
}

const char* la_string_map_get(la_string_map *map, const char *key)
{
    for (size_t i = 0; i < map->length; ++i) {
        if (la_string_eq(key, map->pairs[i]->key)) {
            return map->pairs[i]->value;
        }
    }

    return NULL;
}

void la_string_map_remove(la_string_map *map, const char *key)
{
    la_string_map_pair *pair = NULL;
    size_t pair_idx = 0;
    // Find pair to remove by key.
    for (size_t i = 0; i < map->length; ++i) {
        if (la_string_eq(map->pairs[i]->key, key)) {
            pair = map->pairs[i];
            pair_idx = i;
        }
    }
    // If not found, do nothing.
    if (pair == NULL) {
        return;
    }

    la_string_map_pair_free(pair);
    // Pull pairs pointers to freed position.
    for (size_t i = pair_idx; i < map->length - 1; ++i) {
        map->pairs[i] = map->pairs[i + 1];
    }
    map->pairs[map->length] = NULL;
    map->length -= 1;
}

void la_string_map_free(la_string_map *map)
{
    // Free pairs.
    for (size_t i = 0; i < map->length; ++i) {
        la_string_map_pair_free(map->pairs[i]);
    }

    // Free map.
    free(map);
}


LA_EXTERN_C_END
