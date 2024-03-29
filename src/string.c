#include <laniakea/string.h>

#include <stdlib.h>
#include <string.h>

#include <laniakea/vec.h>

LA_EXTERN_C_BEGIN

void la_string_trim(char *str)
{
    char *start = str;
    char *end = str;
    end += strlen(str) - 1;

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
    while (*end == ' ' || *end == '\n') {
        --end;
    }
    end++;
    *end = '\0';
}

bool la_string_starts_with(const char *str, const char *cmp)
{
    size_t cmp_len = strlen(cmp);
    for (size_t i = 0; i < cmp_len; ++i) {
        if (cmp[i] != str[i]) {
            return false;
        }
    }

    return true;
}

bool la_string_ends_with(const char *str, const char *cmp)
{
    size_t cmp_len = strlen(cmp);
    size_t str_i = strlen(str) - 1;
    size_t cmp_i = strlen(cmp) - 1;
    while (cmp_i > cmp_len) {
        if (cmp[cmp_i] != str[str_i]) {
            return false;
        }
        --str_i;
        --cmp_i;
    }

    return true;
}

ssize_t la_string_find(const char *str, const char *pattern)
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

la_string_vec* la_string_split(const char *str, const char *delim)
{
    la_string_vec *split = la_string_vec_new();

    // If delimiter is larger than str, do not iterate.
    if (strlen(str) < strlen(delim)) {
        la_string_vec_push(split, str);
        return split;
    }

    const char *start = str;
    size_t delim_len = strlen(delim);

    ssize_t found = la_string_find(start, delim);
    while (found != -1) {
        if (found == 0) {
            la_string_vec_push(split, "");
            start += delim_len;
        } else if (found > 0) {
            size_t len = found;
            char *buf = malloc(len + 1);
            strncpy(buf, start, len);
            buf[len] = '\0';
            la_string_vec_push(split, buf);
            free(buf);
            start += len + delim_len;
        }
        found = la_string_find(start, delim);
    }
    // Remains.
    la_string_vec_push(split, start);

    return split;
}

la_string_vec* la_string_splitn(const char *str,
        size_t n, const char *delim)
{
    la_string_vec *split = la_string_vec_new();

    // If delimiter is larger than str, do not iterate.
    if (strlen(str) < strlen(delim)) {
        la_string_vec_push(split, str);
        return split;
    }

    const char *start = str;
    size_t delim_len = strlen(delim);
    size_t pushed = 0;

    ssize_t found = la_string_find(start, delim);
    while (found != -1 && pushed < n - 1) {
        if (found == 0) {
            la_string_vec_push(split, "");
            ++pushed;
            start += delim_len;
        } else if (found > 0) {
            size_t len = found;
            char *buf = malloc(len + 1);
            strncpy(buf, start, len);
            buf[len] = '\0';
            la_string_vec_push(split, buf);
            ++pushed;
            free(buf);
            start += len + delim_len;
        }
        found = la_string_find(start, delim);
    }
    // Remains.
    la_string_vec_push(split, start);

    return split;
}

void la_string_strip_prefix(char *str, const char *prefix)
{
    if (la_string_starts_with(str, prefix)) {
        size_t len = strlen(str) - strlen(prefix);
        strncpy(str, str + strlen(prefix), len);
        str[len] = '\0';
    }
}

void la_string_strip_suffix(char *str, const char *suffix)
{
    if (la_string_ends_with(str, suffix)) {
        size_t len = strlen(str) - strlen(suffix);
        str[len] = '\0';
    }
}

bool la_string_eq(const char *str, const char *other)
{
    if (strcmp(str, other) == 0) {
        return true;
    }
    return false;
}

LA_EXTERN_C_END
