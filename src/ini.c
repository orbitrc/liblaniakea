#include <laniakea/ini.h>

/* C */
#include <stdio.h>
#include <string.h>
/* POSIX */
#include <sys/types.h>

#include <laniakea/string.h>

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

laniakea_ini* laniakea_ini_load(const char *path)
{
    laniakea_ini *ini = laniakea_ini_new();

    FILE *f = fopen(path, "r");

    char *line;
    size_t buf_n = 0;
    ssize_t read_n = 0;
    const char *section;

    while (read_n != -1) {
        read_n = getline(&line, &buf_n, f);
        if (read_n != -1) {
            laniakea_string_trim(line);
            if (laniakea_string_starts_with(line, "[")) {
                section = line;
            } else {
                // laniakea_ini_insert(ini, section, key, value);
            }
        }
    }
    free(line);
}

void laniakea_ini_free(laniakea_ini *ini)
{

}

LANIAKEA_EXTERN_C_END