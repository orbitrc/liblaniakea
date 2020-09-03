#include <laniakea/string.h>

#include <stdlib.h>
#include <string.h>

LANIAKEA_EXTERN_C_BEGIN

void laniakea_string_trim(char *str)
{
    char *start = str;
    char *end = str;

    // Trim leading spaces.
    while (*start != ' ' && *start != '\n') {
        ++start;
    }
    // Case all characters are whitespaces or new-lines.
    if (start == NULL) {
        str = NULL;
    }
    strcpy(str, start);

    // Trim trailing spaces.
    while (*end != ' ' && *end != '\n') {
        ++end;
    }
    end = NULL;
}

laniakea_bool laniakea_string_eq(const char *str, const char *other)
{
    if (strcmp(str, other) == 0) {
        return LANIAKEA_TRUE;
    }
    return LANIAKEA_FALSE;
}

LANIAKEA_EXTERN_C_END