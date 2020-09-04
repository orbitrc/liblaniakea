#ifndef _LANIAKEA_STRING_H
#define _LANIAKEA_STRING_H

#include <laniakea/base.h>

LANIAKEA_EXTERN_C_BEGIN

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
 * Compare strings and returns LANIAKEA_TRUE if those equal.
 */
laniakea_bool laniakea_string_eq(const char *str, const char *other);

LANIAKEA_EXTERN_C_END

#endif /* _LANIAKEA_STRING_H */