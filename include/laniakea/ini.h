#ifndef _LANIAKEA_INI_H
#define _LANIAKEA_INI_H

#include <stdint.h>
#include <stdlib.h>

#include <laniakea/base.h>
#include <laniakea/map.h>

#define LANIAKEA_INI_CAPACITY_MULTIPLE 4

#define LANIAKEA_INI_GET_ERROR_SUCCESS          0
#define LANIAKEA_INI_GET_ERROR_NO_SECTION       1
#define LANIAKEA_INI_GET_ERROR_NO_KEY           2
#define LANIAKEA_INI_GET_ERROR_TYPE_NOT_MATCH   3

LANIAKEA_EXTERN_C_BEGIN

typedef struct laniakea_ini_section {
    char *name;
    laniakea_string_map *map;
} laniakea_ini_section;

typedef struct laniakea_ini {
    size_t length;
    size_t capacity;
    laniakea_ini_section **sections;
} laniakea_ini;


/*==============================*/
/* laniakea_ini_section methods */
/*==============================*/

/**
 * @brief Create new ini section object.
 *
 * @param name The section name which is bracket represented in ini file.
 * @return Newly allocated ini section object.
 */
laniakea_ini_section* laniakea_ini_section_new(const char *name);

/**
 * @brief Insert key/value pair to the section.
 */
void laniakea_ini_section_insert(laniakea_ini_section *section,
        const char *key, const char *value);

/**
 * @brief Get the value from key in the section.
 */
const char* laniakea_ini_section_get(const laniakea_ini_section *section,
        const char *key);

void laniakea_ini_section_free(laniakea_ini_section *section);


/*======================*/
/* laniakea_ini methods */
/*======================*/

/**
 * @brief Create new ini object.
 *
 * @return Newly allocated ini object.
 */
laniakea_ini* laniakea_ini_new();

/**
 * @brief Insert key/value pair to the section.
 *
 * @param ini The ini object.
 * @param section The section.
 * @param key The key.
 * @param value The value.
 */
void laniakea_ini_insert(laniakea_ini *ini, const char *section,
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
const char* laniakea_ini_get_string(const laniakea_ini *ini,
        const char *section, const char *key, int *e);

/**
 * @brief Get value by key from the ini as 32bit integer type.
 *
 * @param ini The ini object.
 * @param section The section.
 * @param key The key for get value.
 * @param e Pointer to recieve error code.
 * @return If e is set to LANIAKEA_INI_GET_ERROR_SUCCESS, the return value is
 *         integer converted value for key.
 *         If e is set to error, the return value is undefined.
 */
int32_t laniakea_ini_get_i32(const laniakea_ini *ini, const char *section,
        const char *key, int *e);

/**
 * @brief Get value by key from the ini as 32bit unsigned integer type.
 *
 * @param ini The ini object.
 * @param section The section.
 * @param key The key for get value.
 * @param e Pointer to recieve error code.
 * @return If e is set to LANIAKEA_INI_GET_ERROR_SUCCESS, the return value is
 *         integer converted value for key.
 *         If e is set to error, the return value is undefined.
 */
uint32_t laniakea_ini_get_u32(const laniakea_ini *ini, const char *section,
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
 * @return LANIAKEA_TRUE or LANIAKEA_FALSE.
 */
laniakea_bool laniakea_ini_get_bool(const laniakea_ini *ini,
        const char *section, const char *key, int *e);

int laniakea_ini_load(laniakea_ini *ini, const char *path);

int laniakea_ini_save(laniakea_ini *ini, const char *path);

void laniakea_ini_free(laniakea_ini *ini);


LANIAKEA_EXTERN_C_END

#endif /* _LANIAKEA_INI_H */