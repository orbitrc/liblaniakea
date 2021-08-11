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

LA_EXTERN_C_BEGIN

la_ini_section* la_ini_section_new(const char *name)
{
    la_ini_section *section = malloc(sizeof(la_ini_section));

    section->name = malloc(strlen(name) + 1);
    strcpy(section->name, name);
    section->map = laniakea_string_map_new();

    return section;
}

void la_ini_section_insert(la_ini_section *section,
        const char *key, const char *value)
{
    laniakea_string_map_insert(section->map, key, value);
}

const char* la_ini_section_get(const la_ini_section *section,
        const char *key)
{
    return laniakea_string_map_get(section->map, key);
}

void la_ini_section_free(la_ini_section *section)
{
    free(section->name);
    laniakea_string_map_free(section->map);

    free(section);
}

/*======================*/
/* laniakea_ini methods */
/*======================*/

la_ini* la_ini_new()
{
    la_ini *ini = malloc(sizeof(la_ini));

    ini->length = 0;
    ini->capacity = LA_INI_CAPACITY_MULTIPLE;
    ini->sections = malloc(sizeof(la_ini_section*)
        * LA_INI_CAPACITY_MULTIPLE);

    return ini;
}

void la_ini_insert(la_ini *ini, const char *section,
        const char *key, const char *value)
{
    // Find section by name.
    la_ini_section *ini_section = NULL;
    for (size_t i = 0; i < ini->length; ++i) {
        if (laniakea_string_eq(section, ini->sections[i]->name)) {
            ini_section = ini->sections[i];
            break;
        }
    }

    // If no section, add one.
    if (ini_section == NULL) {
        ini->sections[ini->length] = la_ini_section_new(section);
        la_ini_section_insert(ini->sections[ini->length],
            key, value);
        ini->length++;
    }
    // If already has section, then add values to there.
    if (ini_section != NULL) {
        la_ini_section_insert(ini_section, key, value);
    }

    // If capacity is full, re-allocate memory.
    if (ini->length == ini->capacity) {
        la_ini_section **new_sections = malloc(
            sizeof(la_ini_section*)
                *
            (ini->capacity + LA_INI_CAPACITY_MULTIPLE)
        );
        ini->capacity += LA_INI_CAPACITY_MULTIPLE;
        for (size_t i = 0; i < ini->length; ++i) {
            new_sections[i] = ini->sections[i];
            new_sections[i]->name = ini->sections[i]->name;
        }
        free(ini->sections);
        ini->sections = new_sections;
    }
}

const char* la_ini_get_string(const la_ini *ini,
        const char *section, const char *key, int *e)
{
    const la_ini_section *sec = NULL;
    for (size_t i = 0; i < ini->length; ++i) {
        if (laniakea_string_eq(ini->sections[i]->name, section)) {
            sec = ini->sections[i];
            break;
        }
    }
    // No section error.
    if (sec == NULL && e != NULL) {
        *e = LA_INI_GET_ERROR_NO_SECTION;
        return NULL;
    }

    // No key error.
    const char *val = la_ini_section_get(sec, key);
    if (val == NULL && e != NULL) {
        *e = LA_INI_GET_ERROR_NO_KEY;
    }

    // Success.
    if (e != NULL) {
        *e = LA_INI_GET_ERROR_SUCCESS;
    }

    return val;
}

int32_t la_ini_get_i32(const la_ini *ini, const char *section,
        const char *key, int *e)
{
    const la_ini_section *sec = NULL;
    for (size_t i = 0; i < ini->length; ++i) {
        if (laniakea_string_eq(ini->sections[i]->name, section)) {
            sec = ini->sections[i];
            break;
        }
    }
    // No section error.
    if (sec == NULL) {
        if (e != NULL) {
            *e = LA_INI_GET_ERROR_NO_SECTION;
        }
        return 0;
    }

    // No key error.
    const char *val = la_ini_section_get(sec, key);
    if (val == NULL) {
        if (e != NULL) {
            *e = LA_INI_GET_ERROR_NO_KEY;
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
            *e = LA_INI_GET_ERROR_TYPE_NOT_MATCH;
        }
        return 0;
    }

    // Success.
    if (e != NULL) {
        *e = LA_INI_GET_ERROR_SUCCESS;
    }

    return ret;
}

uint32_t la_ini_get_u32(const la_ini *ini, const char *section,
        const char *key, int *e)
{
    const la_ini_section *sec = NULL;
    for (size_t i = 0; i < ini->length; ++i) {
        if (laniakea_string_eq(ini->sections[i]->name, section)) {
            sec = ini->sections[i];
            break;
        }
    }
    // No section error.
    if (sec == NULL) {
        if (e != NULL) {
            *e = LA_INI_GET_ERROR_NO_SECTION;
        }
        return 0;
    }

    // No key error.
    const char *val = la_ini_section_get(sec, key);
    if (val == NULL) {
        if (e != NULL) {
            *e = LA_INI_GET_ERROR_NO_KEY;
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
            *e = LA_INI_GET_ERROR_TYPE_NOT_MATCH;
        }
        return 0;
    }

    // Success.
    if (e != NULL) {
        *e = LA_INI_GET_ERROR_SUCCESS;
    }

    return ret;
}

bool la_ini_get_bool(const la_ini *ini,
        const char *section, const char *key, int *e)
{
    const la_ini_section *sec = NULL;
    for (size_t i = 0; i < ini->length; ++i) {
        if (laniakea_string_eq(ini->sections[i]->name, section)) {
            sec = ini->sections[i];
            break;
        }
    }
    // No section error.
    if (sec == NULL) {
        if (e != NULL) {
            *e = LA_INI_GET_ERROR_NO_SECTION;
        }
        return 0;
    }

    // No key error.
    const char *val = la_ini_section_get(sec, key);
    if (val == NULL) {
        if (e != NULL) {
            *e = LA_INI_GET_ERROR_NO_KEY;
        }
        return 0;
    }

    if (laniakea_string_eq(val, "true")) {
        if (e != NULL) {
            *e = LA_INI_GET_ERROR_SUCCESS;
        }
        return true;
    }
    if (laniakea_string_eq(val, "false")) {
        if (e != NULL) {
            *e = LA_INI_GET_ERROR_SUCCESS;
        }
        return false;
    }

    // Type not match error.
    if (e != NULL) {
        *e = LA_INI_GET_ERROR_TYPE_NOT_MATCH;
    }
    return false;
}

int la_ini_load(la_ini *ini, const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        switch (errno) {
        case ENOENT:
            return LA_FILE_ERROR_NO_FILE;
        case EACCES:
            return LA_FILE_ERROR_PERMISSION;
        default:
            return LA_FILE_ERROR_UNKNOWN;
        }
    }

    char *line;
    size_t buf_n = 0;
    ssize_t read_n = 0;
    char *section = NULL;

    while (read_n != -1) {
        read_n = getline(&line, &buf_n, f);
        if (read_n != -1) {
            laniakea_string_trim(line);
            if (laniakea_string_starts_with(line, "[")) {
                if (section != NULL) {
                    free(section);
                }
                section = malloc(strlen(line));
                strcpy(section, line);
                // Strip [, ].
                laniakea_string_strip_prefix(section, "[");
                laniakea_string_strip_suffix(section, "]");
            } else if (laniakea_string_eq(line, "")) {
                continue;
            } else {
                laniakea_string_vec *kv;
                kv = laniakea_string_splitn(line, 2, "=");
                printf(" - section: %s\n", section);
                printf("key: %s, value: %s\n",
                    laniakea_string_vec_get(kv, 0),
                    laniakea_string_vec_get(kv, 1)
                );
                la_ini_insert(ini, section,
                    laniakea_string_vec_get(kv, 0),
                    laniakea_string_vec_get(kv, 1));
                laniakea_string_vec_free(kv);
            }
        }
    }
    if (section != NULL) {
        free(section);
    }
    
    free(line);
    fclose(f);

    return LA_FILE_ERROR_SUCCESS;
}

int la_ini_save(la_ini *ini, const char *path)
{
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        switch (errno) {
        case ENOENT:
            return LA_FILE_ERROR_NO_DIRECTORY;
        case EACCES:
            return LA_FILE_ERROR_PERMISSION;
        default:
            return LA_FILE_ERROR_UNKNOWN;
        }
    }

    for (size_t i = 0; i < ini->length; ++i) {
        // Write section name.
        fprintf(f, "[%s]\n", ini->sections[i]->name);
        for (size_t j = 0; j < ini->sections[i]->map->length; ++j) {
            // Write key=value pairs.
            fprintf(f, "%s=%s\n",
                ini->sections[i]->map->pairs[j]->key,
                ini->sections[i]->map->pairs[j]->value
            );
        }
        fprintf(f, "\n");
    }

    fclose(f);

    return LA_FILE_ERROR_SUCCESS;
}

void la_ini_free(la_ini *ini)
{
    for (size_t i = 0; i < ini->length; ++i) {
        la_ini_section_free(ini->sections[i]);
    }

    free(ini);
}

LA_EXTERN_C_END
