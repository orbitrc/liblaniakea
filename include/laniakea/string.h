#ifndef _LANIAKEA_STRING_H
#define _LANIAKEA_STRING_H

#include <sys/types.h>

#include <laniakea/base.h>

LANIAKEA_EXTERN_C_BEGIN

typedef struct laniakea_string_vec laniakea_string_vec;

/**
 * Remove leading/trailing whitespaces and new-lines.
 */
void laniakea_string_trim(char *str);

/**
 * Check if the string is starts with given string part.
 *
 * @param str String that check.
 * @param str String part that check if starts with.
 * @return True if starts with cmp, else false.
 */
laniakea_bool laniakea_string_starts_with(const char *str, const char *cmp);

/**
 * Find the index of first matching pattern.
 *
 * @param str Source string.
 * @param pattern String that find.
 * @return The index of first matching. If not found pattern, returns -1.
 */
ssize_t laniakea_string_find(const char *str, const char *pattern);

laniakea_string_vec* laniakea_string_split(const char *str, const char *delim);

laniakea_string_vec* laniakea_string_splitn(const char *str,
        size_t n, const char *delim);

/**
 * Compare strings and returns LANIAKEA_TRUE if those equal.
 */
laniakea_bool laniakea_string_eq(const char *str, const char *other);

LANIAKEA_EXTERN_C_END

#endif /* _LANIAKEA_STRING_H */