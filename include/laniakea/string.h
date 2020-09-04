#ifndef _LANIAKEA_STRING_H
#define _LANIAKEA_STRING_H

#include <laniakea/base.h>

LANIAKEA_EXTERN_C_BEGIN

/**
 * Remove leading/trailing whitespaces and new-lines.
 */
void laniakea_string_trim(char *str);


/**
 * Compare strings and returns LANIAKEA_TRUE if those equal.
 */
laniakea_bool laniakea_string_eq(const char *str, const char *other);

LANIAKEA_EXTERN_C_END

#endif /* _LANIAKEA_STRING_H */