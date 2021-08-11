#ifndef _LANIAKEA_MAP_H
#define _LANIAKEA_MAP_H

#include <stdlib.h>

#include <laniakea/base.h>

#define LA_MAP_CAPACITY_MULTIPLE 4

LA_EXTERN_C_BEGIN

typedef struct la_string_map_pair {
    char *key;
    char *value;
} la_string_map_pair;

typedef struct la_string_map {
    size_t length;
    size_t capacity;
    la_string_map_pair **pairs;
} la_string_map;


/*============================*/
/* la_string_map_pair methods */
/*============================*/

/**
 * @brief Create new string map pair with given key and value.
 *
 * @param key The key.
 * @param value The value.
 * @return Newly created key/value pair.
 */
la_string_map_pair* la_string_map_pair_new(const char *key,
        const char *value);

/**
 * @brief Free the allocated string map pair.
 *
 * @param pair The pair that will be deleted.
 */
void la_string_map_pair_free(la_string_map_pair *pair);


/*=======================*/
/* la_string_map methods */
/*=======================*/

/**
 * @brief Create new string map.
 *
 * @return Newly created empty string map.
 */
la_string_map* la_string_map_new();

/**
 * @brief Check if key is in the map.
 *
 * @return Boolean.
 */
bool la_string_map_contains(const la_string_map *map,
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
void la_string_map_insert(la_string_map *map,
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
const char* la_string_map_get(la_string_map *map, const char *key);

/**
 * @brief Remove the key from the map.
 */
void la_string_map_remove(la_string_map *map, const char *key);

/**
 * @brief Free the string map.
 *
 * @param map The string map.
 */
void la_string_map_free(la_string_map *map);

LA_EXTERN_C_END

#endif /* _LANIAKEA_MAP_H */
