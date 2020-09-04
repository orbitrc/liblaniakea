#ifndef _LANIAKEA_PREFERENCES_H
#define _LANIAKEA_PREFERENCES_H

#include <stdint.h>
#include <stdlib.h>

#include <laniakea/base.h>

#define LANIAKEA_PREFERENCES_CONFIG_PATH ".config/laniakea/preferences.conf"

LANIAKEA_EXTERN_C_BEGIN

#define LANIAKEA_ERROR_SUCCESS      0
#define LANIAKEA_ERROR_NO_SUCH_FILE 1

typedef struct laniakea_preferences {
    // Display.
    void *scales;
    // Desktop.
    char *wallpaper;
    size_t number_of_desktops;
    // Keyboard.
    int16_t delay_until_repeat; // 0-10,000
    uint8_t key_repeat;         // 0-255

} laniakea_preferences;


/**
 * @brief Create new laniakea_preferences object.
 *
 * @return Newly allocated laniakea_preferences object.
 */
laniakea_preferences* laniakea_preferences_new();


/**
 * @brief Load config file from disk.
 * 
 * @param preferences The laniakea_preferences object.
 * @return Error code.
 */
int laniakea_preferences_load(laniakea_preferences *preferences);

LANIAKEA_EXTERN_C_END

#endif /* _LANIAKEA_PREFERENCES_H */
