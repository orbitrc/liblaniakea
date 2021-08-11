#ifndef _LANIAKEA_INI_H
#define _LANIAKEA_INI_H

#include <stdint.h>
#include <stdlib.h>

#include <laniakea/base.h>
#include <laniakea/map.h>

#define LA_INI_CAPACITY_MULTIPLE 4

#define LA_INI_GET_ERROR_SUCCESS            0
#define LA_INI_GET_ERROR_NO_SECTION         1
#define LA_INI_GET_ERROR_NO_KEY             2
#define LA_INI_GET_ERROR_TYPE_NOT_MATCH     3

LA_EXTERN_C_BEGIN

typedef struct la_ini_section {
    char *name;
    laniakea_string_map *map;
} la_ini_section;

typedef struct la_ini {
    size_t length;
    size_t capacity;
    la_ini_section **sections;
} la_ini;


/*==============================*/
/* la_ini_section methods */
/*==============================*/

/**
 * @brief Create new ini section object.
 *
 * @param name The section name which is bracket represented in ini file.
 * @return Newly allocated ini section object.
 */
la_ini_section* la_ini_section_new(const char *name);

/**
 * @brief Insert key/value pair to the section.
 */
void la_ini_section_insert(la_ini_section *section,
        const char *key, const char *value);

/**
 * @brief Get the value from key in the section.
 */
const char* la_ini_section_get(const la_ini_section *section,
        const char *key);

void la_ini_section_free(la_ini_section *section);


/*======================*/
/* la_ini methods */
/*======================*/

/**
 * @brief Create new ini object.
 *
 * @return Newly allocated ini object.
 */
la_ini* la_ini_new();

/**
 * @brief Insert key/value pair to the section.
 *
 * @param ini The ini object.
 * @param section The section.
 * @param key The key.
 * @param value The value.
 */
void la_ini_insert(la_ini *ini, const char *section,
        const char *key, const char *value);

/**
 * @brief Get value by key from the ini as c string type.
 *
 * @param ini The ini object.
 * @param section The section.
 * @param key The key for get value.
 * @param e Pointer to receive error code.
 * @return Value for key or NULL.
 */
const char* la_ini_get_string(const la_ini *ini,
        const char *section, const char *key, int *e);

/**
 * @brief Get value by key from the ini as 32bit integer type.
 *
 * @param ini The ini object.
 * @param section The section.
 * @param key The key for get value.
 * @param e Pointer to recieve error code.
 * @return If e is set to LA_INI_GET_ERROR_SUCCESS, the return value is
 *         integer converted value for key.
 *         If e is set to error, the return value is undefined.
 */
int32_t la_ini_get_i32(const la_ini *ini, const char *section,
        const char *key, int *e);

/**
 * @brief Get value by key from the ini as 32bit unsigned integer type.
 *
 * @param ini The ini object.
 * @param section The section.
 * @param key The key for get value.
 * @param e Pointer to recieve error code.
 * @return If e is set to LA_INI_GET_ERROR_SUCCESS, the return value is
 *         integer converted value for key.
 *         If e is set to error, the return value is undefined.
 */
uint32_t la_ini_get_u32(const la_ini *ini, const char *section,
        const char *key, int *e);

/**
 * @brief Get value by key from the ini as boolean type.
 *
 * Boolean type is "true" for true, "false" for false, and case sensitive.
 *
 * @param ini The ini object.
 * @param section The section.
 * @param key The key for get value.
 * @param e Pointer to recieve error code.
 * @return true or false.
 */
bool la_ini_get_bool(const la_ini *ini,
        const char *section, const char *key, int *e);

int la_ini_load(la_ini *ini, const char *path);

int la_ini_save(la_ini *ini, const char *path);

void la_ini_free(la_ini *ini);


LA_EXTERN_C_END

#endif /* _LANIAKEA_INI_H */
