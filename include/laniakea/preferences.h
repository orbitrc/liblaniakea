#ifndef _LANIAKEA_PREFERENCES_H
#define _LANIAKEA_PREFERENCES_H

#include <stdint.h>
#include <stdlib.h>

#include <laniakea/base.h>

#define LANIAKEA_PREFERENCES_CONFIG_PATH ".config/laniakea/preferences.conf"

#define LANIAKEA_PREFERENCES_DEFAULT_DESKTOP_NUMBER_OF_DESKTOPS 4
#define LANIAKEA_PREFERENCES_DEFAULT_KEYBOARD_DELAY_UNTIL_REPEAT 600
#define LANIAKEA_PREFERENCES_DEFAULT_KEYBOARD_KEY_REPEAT 25
#define LANIAKEA_PREFERENCES_DEFAULT_POWER_SHOW_BATTERY_IN_MENU_BAR LANIAKEA_TRUE

LANIAKEA_EXTERN_C_BEGIN

typedef struct laniakea_ini laniakea_ini;

typedef struct laniakea_preferences {
    // - Appearance
    // bool dark_mode;
    // - Display.
    // void *scales;
    // - Desktop.
    // char *wallpaper;
    // size_t number_of_desktops;
    // - Keyboard.
    // int16_t delay_until_repeat; // 0-10,000
    // uint8_t key_repeat;         // 0-255
    laniakea_ini *conf;
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


/*====================*/
/* Appearance get/set */
/*====================*/

laniakea_bool laniakea_preferences_dark_mode(laniakea_preferences *preferences);

void laniakea_preferences_set_dark_mode(laniakea_preferences *preferences,
        laniakea_bool value);

/*=================*/
/* Display get/set */
/*=================*/


/*=================*/
/* Desktop get/set */
/*=================*/

LANIAKEA_EXTERN_C_END

#endif /* _LANIAKEA_PREFERENCES_H */
