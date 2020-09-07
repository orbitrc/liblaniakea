#include <laniakea/ini.h>

/* C */
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* POSIX */
#include <sys/types.h>

#include <laniakea/base.h>
#include <laniakea/string.h>
#include <laniakea/vec.h>

LANIAKEA_EXTERN_C_BEGIN

laniakea_ini_section* laniakea_ini_section_new(const char *name)
{
    laniakea_ini_section *section = malloc(sizeof(laniakea_ini_section));

    section->name = malloc(sizeof(char) * strlen(name) + 1);
    strcpy(section->name, name);
    section->map = laniakea_string_map_new();

    return section;
}

void laniakea_ini_section_insert(laniakea_ini_section *section,
        const char *key, const char *value)
{
    laniakea_string_map_insert(section->map, key, value);
}

const char* laniakea_ini_section_get(const laniakea_ini_section *section,
        const char *key)
{
    return laniakea_string_map_get(section->map, key);
}

void laniakea_ini_section_free(laniakea_ini_section *section)
{
    free(section->name);
    laniakea_string_map_free(section->map);

    free(section);
}

/*======================*/
/* laniakea_ini methods */
/*======================*/

laniakea_ini* laniakea_ini_new()
{
    laniakea_ini *ini = malloc(sizeof(laniakea_ini));

    ini->length = 0;
    ini->capacity = LANIAKEA_INI_CAPACITY_MULTIPLE;
    ini->sections = malloc(sizeof(laniakea_ini_section*)
        * LANIAKEA_INI_CAPACITY_MULTIPLE);

    return ini;
}

void laniakea_ini_insert(laniakea_ini *ini, const char *section,
        const char *key, const char *value)
{
    // Find section by name.
    laniakea_ini_section *ini_section = NULL;
    for (size_t i = 0; i < ini->length; ++i) {
        if (laniakea_string_eq(section, ini->sections[i]->name)) {
            ini_section = ini->sections[i];
            break;
        }
    }

    // If no section, add one.
    if (ini_section == NULL) {
        ini->sections[ini->length] = laniakea_ini_section_new(section);
        laniakea_ini_section_insert(ini->sections[ini->length],
            key, value);
        ini->length++;
    }
    // If already has section, then add values to there.
    if (ini_section != NULL) {
        laniakea_ini_section_insert(ini_section, key, value);
        ini->length++;
    }

    // If capacity is full, re-allocate memory.
    if (ini->length == ini->capacity) {
        laniakea_ini_section **new_sections = malloc(
            sizeof(laniakea_ini_section*)
                *
            ini->capacity + LANIAKEA_INI_CAPACITY_MULTIPLE
        );
        ini->capacity += LANIAKEA_INI_CAPACITY_MULTIPLE;
        for (size_t i = 0; i < ini->length; ++i) {
            new_sections[i]->name = ini->sections[i]->name;
            new_sections[i] = ini->sections[i];
        }
        free(ini->sections);
        ini->sections = new_sections;
    }
}

const char* laniakea_ini_get_string(const laniakea_ini *ini,
        const char *section, const char *key, int *e)
{
    const laniakea_ini_section *sec = NULL;
    for (size_t i = 0; i < ini->length; ++i) {
        if (laniakea_string_eq(ini->sections[i]->name, section)) {
            sec = ini->sections[i];
            break;
        }
    }
    // No section error.
    if (sec == NULL && e != NULL) {
        *e = LANIAKEA_INI_GET_ERROR_NO_SECTION;
        return NULL;
    }

    // No key error.
    const char *val = laniakea_ini_section_get(sec, key);
    if (val == NULL && e != NULL) {
        *e = LANIAKEA_INI_GET_ERROR_NO_KEY;
    }

    // Success.
    if (e != NULL) {
        *e = LANIAKEA_INI_GET_ERROR_SUCCESS;
    }

    return val;
}

int32_t laniakea_ini_get_i32(const laniakea_ini *ini, const char *section,
        const char *key, int *e)
{
    const laniakea_ini_section *sec = NULL;
    for (size_t i = 0; i < ini->length; ++i) {
        if (laniakea_string_eq(ini->sections[i]->name, section)) {
            sec = ini->sections[i];
            break;
        }
    }
    // No section error.
    if (sec == NULL) {
        if (e != NULL) {
            *e = LANIAKEA_INI_GET_ERROR_NO_SECTION;
        }
        return 0;
    }

    // No key error.
    const char *val = laniakea_ini_section_get(sec, key);
    if (val == NULL) {
        if (e != NULL) {
            *e = LANIAKEA_INI_GET_ERROR_NO_KEY;
        }
        return 0;
    }

    // Type not match error.
    // TODO: Validate all characters.
    errno = 0;
    char *end;
    int32_t ret = strtol(val, &end, 10);
    if (errno == ERANGE) {
        if (e != NULL) {
            *e = LANIAKEA_INI_GET_ERROR_TYPE_NOT_MATCH;
        }
        return 0;
    }

    // Success.
    if (e != NULL) {
        *e = LANIAKEA_INI_GET_ERROR_SUCCESS;
    }

    return ret;
}

uint32_t laniakea_ini_get_u32(const laniakea_ini *ini, const char *section,
        const char *key, int *e)
{
    const laniakea_ini_section *sec = NULL;
    for (size_t i = 0; i < ini->length; ++i) {
        if (laniakea_string_eq(ini->sections[i]->name, section)) {
            sec = ini->sections[i];
            break;
        }
    }
    // No section error.
    if (sec == NULL) {
        if (e != NULL) {
            *e = LANIAKEA_INI_GET_ERROR_NO_SECTION;
        }
        return 0;
    }

    // No key error.
    const char *val = laniakea_ini_section_get(sec, key);
    if (val == NULL) {
        if (e != NULL) {
            *e = LANIAKEA_INI_GET_ERROR_NO_KEY;
        }
        return 0;
    }

    // Type not match error.
    // TODO: Validate all characters.
    // TODO: Validate negative number.
    errno = 0;
    char *end;
    uint32_t ret = strtol(val, &end, 10);
    if (errno == ERANGE) {
        if (e != NULL) {
            *e = LANIAKEA_INI_GET_ERROR_TYPE_NOT_MATCH;
        }
        return 0;
    }

    // Success.
    if (e != NULL) {
        *e = LANIAKEA_INI_GET_ERROR_SUCCESS;
    }

    return ret;
}

laniakea_bool laniakea_ini_get_bool(const laniakea_ini *ini,
        const char *section, const char *key, int *e)
{
    const laniakea_ini_section *sec = NULL;
    for (size_t i = 0; i < ini->length; ++i) {
        if (laniakea_string_eq(ini->sections[i]->name, section)) {
            sec = ini->sections[i];
            break;
        }
    }
    // No section error.
    if (sec == NULL) {
        if (e != NULL) {
            *e = LANIAKEA_INI_GET_ERROR_NO_SECTION;
        }
        return 0;
    }

    // No key error.
    const char *val = laniakea_ini_section_get(sec, key);
    if (val == NULL) {
        if (e != NULL) {
            *e = LANIAKEA_INI_GET_ERROR_NO_KEY;
        }
        return 0;
    }

    if (laniakea_string_eq(val, "true")) {
        if (e != NULL) {
            *e = LANIAKEA_INI_GET_ERROR_SUCCESS;
        }
        return LANIAKEA_TRUE;
    }
    if (laniakea_string_eq(val, "false")) {
        if (e != NULL) {
            *e = LANIAKEA_INI_GET_ERROR_SUCCESS;
        }
        return LANIAKEA_FALSE;
    }

    // Type not match error.
    if (e != NULL) {
        *e = LANIAKEA_INI_GET_ERROR_TYPE_NOT_MATCH;
    }
    return LANIAKEA_FALSE;
}

int laniakea_ini_load(laniakea_ini *ini, const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        switch (errno) {
        case ENOENT:
            return LANIAKEA_FILE_ERROR_NO_FILE;
        case EACCES:
            return LANIAKEA_FILE_ERROR_PERMISSION;
        default:
            return LANIAKEA_FILE_ERROR_UNKNOWN;
        }
    }

    char *line;
    size_t buf_n = 0;
    ssize_t read_n = 0;
    const char *section;

    while (read_n != -1) {
        read_n = getline(&line, &buf_n, f);
        if (read_n != -1) {
            laniakea_string_trim(line);
            printf("line: %s\n", line);
            if (laniakea_string_starts_with(line, "[")) {
                section = line;
            } else if (laniakea_string_eq(line, "")) {
                continue;
            } else {
                laniakea_string_vec *kv;
                kv = laniakea_string_splitn(line, 2, "=");
                laniakea_ini_insert(ini, section,
                    laniakea_string_vec_get(kv, 0),
                    laniakea_string_vec_get(kv, 1));
                laniakea_string_vec_free(kv);
            }
        }
    }
    free(line);
    fclose(f);

    return LANIAKEA_FILE_ERROR_SUCCESS;
}

void laniakea_ini_free(laniakea_ini *ini)
{
    for (size_t i = 0; i < ini->length; ++i) {
        laniakea_ini_section_free(ini->sections[i]);
    }

    free(ini);
}

LANIAKEA_EXTERN_C_END