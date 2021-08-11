#ifndef _LANIAKEA_STRING_H
#define _LANIAKEA_STRING_H

#include <sys/types.h>

#include <laniakea/base.h>

LA_EXTERN_C_BEGIN

typedef struct la_string_vec la_string_vec;

/**
 * Remove leading/trailing whitespaces and new-lines.
 */
void la_string_trim(char *str);

/**
 * Check if the string is starts with given string part.
 *
 * @param str String that check.
 * @param cmp String part that check if starts with.
 * @return True if starts with cmp, else false.
 */
bool la_string_starts_with(const char *str, const char *cmp);

/**
 * @brief Check if the string is ends with given string part.
 *
 * @param str String that check.
 * @param cmp String part that check if ends with.
 * @return True if ends with cmp, else false.
 */
bool la_string_ends_with(const char *str, const char *cmp);

/**
 * Find the index of first matching pattern.
 *
 * @param str Source string.
 * @param pattern String that find.
 * @return The index of first matching. If not found pattern, returns -1.
 */
ssize_t la_string_find(const char *str, const char *pattern);

la_string_vec* la_string_split(const char *str, const char *delim);

la_string_vec* la_string_splitn(const char *str, size_t n, const char *delim);

/**
 * @brief Remove given prefix from the string.
 */
void la_string_strip_prefix(char *str, const char *prefix);

/**
 * @brief Remove given suffix from the string.
 */
void la_string_strip_suffix(char *str, const char *suffix);

/**
 * Compare strings and returns true if those equal.
 */
bool la_string_eq(const char *str, const char *other);

LA_EXTERN_C_END

#endif /* _LANIAKEA_STRING_H */
