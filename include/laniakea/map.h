#ifndef _LANIAKEA_MAP_H
#define _LANIAKEA_MAP_H

#include <stdlib.h>

#include <laniakea/base.h>

#define LANIAKEA_MAP_CAPACITY_MULTIPLE 4

LANIAKEA_EXTERN_C_BEGIN

typedef struct laniakea_string_map_pair {
    char *key;
    char *value;
} laniakea_string_map_pair;

typedef struct laniakea_string_map {
    size_t length;
    size_t capacity;
    laniakea_string_map_pair **pairs;
} laniakea_string_map;


/*==================================*/
/* laniakea_string_map_pair methods */
/*==================================*/

/**
 * @brief Create new string map pair with given key and value.
 *
 * @param key The key.
 * @param value The value.
 * @return Newly created key/value pair.
 */
laniakea_string_map_pair* laniakea_string_map_pair_new(const char *key,
        const char *value);

/**
 * @brief Free the allocated string map pair.
 *
 * @param pair The pair that will be deleted.
 */
void laniakea_string_map_pair_free(laniakea_string_map_pair *pair);


/*=============================*/
/* laniakea_string_map methods */
/*=============================*/

/**
 * @brief Create new string map.
 *
 * @return Newly created empty string map.
 */
laniakea_string_map* laniakea_string_map_new();

/**
 * @brief Check if key is in the map.
 *
 * @return Boolean.
 */
laniakea_bool laniakea_string_map_contains(const laniakea_string_map *map,
        const char *key);

/**
 * @brief Insert value with key to the map.
 *
 * If the length of key/value pair is equal to capacity after insert,
 * The capacity is automatically grown.
 * When the key is already exists, then old pair will be free and new pair is
 * created and inserted.
 *
 * @param map Map to insert.
 * @param key The key.
 * @param value The value.
 */
void laniakea_string_map_insert(laniakea_string_map *map,
        const char *key, const char *value);

/**
 * @brief Get the value by key from map.
 *
 * Note that the returned value is a reference so if the map's capacity is
 * grown, the source is de-allocated from the memory.
 *
 * @return A reference of value about key. If no value for key found, returns
 *         NULL.
 */
const char* laniakea_string_map_get(laniakea_string_map *map, const char *key);

/**
 * @brief Remove the key from the map.
 */
void laniakea_string_map_remove(laniakea_string_map *map, const char *key);

/**
 * @brief Free the string map.
 *
 * @param map The string map.
 */
void laniakea_string_map_free(laniakea_string_map *map);

LANIAKEA_EXTERN_C_END

#endif /* _LANIAKEA_MAP_H */