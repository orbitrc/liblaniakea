#ifndef _LANIAKEA_INI_H
#define _LANIAKEA_INI_H

#include <stdlib.h>

#include <laniakea/base.h>
#include <laniakea/map.h>

#define LANIAKEA_INI_CAPACITY_MULTIPLE 4

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

laniakea_ini_section* laniakea_ini_section_new(const char *name);
void laniakea_ini_section_insert(laniakea_ini_section *section,
        const char *key, const char *value);
const char* laniakea_ini_section_get(const laniakea_ini_section *section,
        const char *key);
void laniakea_ini_section_free(laniakea_ini_section *section);


/*======================*/
/* laniakea_ini methods */
/*======================*/

laniakea_ini* laniakea_ini_new();
void laniakea_ini_insert(laniakea_ini *ini, const char *section,
        const char *key, const char *value);
int laniakea_ini_load(laniakea_ini *ini, const char *path);
void laniakea_ini_free(laniakea_ini *ini);


LANIAKEA_EXTERN_C_END

#endif /* _LANIAKEA_INI_H */