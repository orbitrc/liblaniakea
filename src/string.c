#include <laniakea/string.h>

#include <stdlib.h>
#include <string.h>

#include <laniakea/vec.h>

LANIAKEA_EXTERN_C_BEGIN

void laniakea_string_trim(char *str)
{
    char *start = str;
    char *end = str;

    // Trim leading spaces.
    while (*start == ' ' || *start == '\n') {
        ++start;
    }
    // Case all characters are whitespaces or new-lines.
    if (*start == '\0') {
        *str = '\0';
    }
    strcpy(str, start);

    // Trim trailing spaces.
    while (*end != ' ' && *end != '\n') {
        ++end;
    }
    *end = '\0';
}

laniakea_bool laniakea_string_starts_with(const char *str, const char *cmp)
{
    size_t cmp_len = strlen(cmp);
    for (size_t i = 0; i < cmp_len; ++i) {
        if (cmp[i] != str[i]) {
            return LANIAKEA_FALSE;
        }
    }

    return LANIAKEA_TRUE;
}

ssize_t laniakea_string_find(const char *str, const char *pattern)
{
    size_t pat_len = strlen(pattern);
    const char *iter = str;
    while (*iter != '\0') {
        if (strncmp(iter, pattern, pat_len) == 0) {
            break;
        }
        ++iter;
    }

    if (*iter == '\0') {
        return -1;
    }
    return iter - str;
}

laniakea_string_vec* laniakea_string_split(const char *str, const char *delim)
{
    laniakea_string_vec *split = laniakea_string_vec_new();

    // If delimiter is larger than str, do not iterate.
    if (strlen(str) < strlen(delim)) {
        laniakea_string_vec_push(split, str);
        return split;
    }

    const char *start = str;
    size_t delim_len = strlen(delim);

    ssize_t found = laniakea_string_find(start, delim);
    while (found != -1) {
        if (found == 0) {
            laniakea_string_vec_push(split, "");
            start += delim_len;
        } else if (found > 0) {
            size_t len = found;
            char *buf = malloc(len + 1);
            strncpy(buf, start, len);
            buf[len] = '\0';
            laniakea_string_vec_push(split, buf);
            free(buf);
            start += len + delim_len;
        }
        found = laniakea_string_find(start, delim);
    }
    // Remains.
    laniakea_string_vec_push(split, start);

    return split;
}

laniakea_string_vec* laniakea_string_splitn(const char *str,
        size_t n, const char *delim)
{
    laniakea_string_vec *split = laniakea_string_vec_new();

    // If delimiter is larger than str, do not iterate.
    if (strlen(str) < strlen(delim)) {
        laniakea_string_vec_push(split, str);
        return split;
    }

    const char *start = str;
    size_t delim_len = strlen(delim);
    size_t pushed = 0;

    ssize_t found = laniakea_string_find(start, delim);
    while (found != -1 && pushed < n - 1) {
        if (found == 0) {
            laniakea_string_vec_push(split, "");
            ++pushed;
            start += delim_len;
        } else if (found > 0) {
            size_t len = found;
            char *buf = malloc(len + 1);
            strncpy(buf, start, len);
            buf[len] = '\0';
            laniakea_string_vec_push(split, buf);
            ++pushed;
            free(buf);
            start += len + delim_len;
        }
        found = laniakea_string_find(start, delim);
    }
    // Remains.
    laniakea_string_vec_push(split, start);

    return split;
}

laniakea_bool laniakea_string_eq(const char *str, const char *other)
{
    if (strcmp(str, other) == 0) {
        return LANIAKEA_TRUE;
    }
    return LANIAKEA_FALSE;
}

LANIAKEA_EXTERN_C_END