#include <laniakea/map.h>

#include <string.h>

#include <laniakea/base.h>
#include <laniakea/string.h>

LANIAKEA_EXTERN_C_BEGIN


/*==================================*/
/* laniakea_string_map_pair methods */
/*==================================*/

laniakea_string_map_pair* laniakea_string_map_pair_new(const char *key,
        const char *value)
{
    laniakea_string_map_pair *pair;
    // Initialize pair.
    pair = malloc(sizeof(laniakea_string_map_pair));
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

void laniakea_string_map_pair_free(laniakea_string_map_pair *pair)
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
/* laniakea_string_map methods */
/*=============================*/

laniakea_string_map* laniakea_string_map_new()
{
    laniakea_string_map *map;
    // Initialize map.
    map = malloc(sizeof(laniakea_string_map));
    map->length = 0;
    map->capacity = LANIAKEA_MAP_CAPACITY_MULTIPLE;
    map->pairs = malloc(sizeof(laniakea_string_map_pair*)
        * LANIAKEA_MAP_CAPACITY_MULTIPLE);

    return map;
}

laniakea_bool laniakea_string_map_contains(const laniakea_string_map *map,
        const char *key)
{
    for (size_t i = 0; i < map->length; ++i) {
        if (laniakea_string_eq(map->pairs[i]->key, key)) {
            return LANIAKEA_TRUE;
        }
    }

    return LANIAKEA_FALSE;
}

void laniakea_string_map_insert(laniakea_string_map *map,
        const char *key, const char *value)
{
    // If key already exists, replace.
    if (laniakea_string_map_contains(map, key)) {
        laniakea_string_map_remove(map, key);
        laniakea_string_map_insert(map, key, value);

        return;
    }

    laniakea_string_map_pair *pair = laniakea_string_map_pair_new(key, value);
    map->pairs[map->length] = pair;
    map->length++;

    // If capacity is full, re-allocate more memory.
    if (map->length == map->capacity) {
        // Re-allocate more size.
        laniakea_string_map_pair **new_pairs = malloc(
            sizeof(laniakea_string_map_pair*)
                *
            (map->capacity + LANIAKEA_MAP_CAPACITY_MULTIPLE)
        );
        // Copy pairs to new memory space.
        for (size_t i = 0; i < map->length; ++i) {
            new_pairs[i] = laniakea_string_map_pair_new(
                map->pairs[i]->key, map->pairs[i]->value);
        }
        // Free old pairs.
        for (size_t i = 0; i < map->length; ++i) {
            laniakea_string_map_pair_free(map->pairs[i]);
        }
        free(map->pairs);
        // Replace old pairs to new pairs.
        map->pairs = new_pairs;
        map->capacity += LANIAKEA_MAP_CAPACITY_MULTIPLE;
    }
}

const char* laniakea_string_map_get(laniakea_string_map *map, const char *key)
{
    for (size_t i = 0; i < map->length; ++i) {
        if (laniakea_string_eq(key, map->pairs[i]->key)) {
            return map->pairs[i]->value;
        }
    }

    return NULL;
}

void laniakea_string_map_remove(laniakea_string_map *map, const char *key)
{
    laniakea_string_map_pair *pair = NULL;
    size_t pair_idx = 0;
    // Find pair to remove by key.
    for (size_t i = 0; i < map->length; ++i) {
        if (laniakea_string_eq(map->pairs[i]->key, key)) {
            pair = map->pairs[i];
            pair_idx = i;
        }
    }
    // If not found, do nothing.
    if (pair == NULL) {
        return;
    }

    laniakea_string_map_pair_free(pair);
    // Pull pairs pointers to freed position.
    for (size_t i = pair_idx; i < map->length - 1; ++i) {
        map->pairs[i] = map->pairs[i + 1];
    }
    map->pairs[map->length] = NULL;
    map->length -= 1;
}

void laniakea_string_map_free(laniakea_string_map *map)
{
    // Free pairs.
    for (size_t i = 0; i < map->length; ++i) {
        laniakea_string_map_pair_free(map->pairs[i]);
    }

    // Free map.
    free(map);
}


LANIAKEA_EXTERN_C_END