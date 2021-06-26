#ifndef _LANIAKEA_PREFERENCES_H
#define _LANIAKEA_PREFERENCES_H

#include <stdint.h>
#include <stdlib.h>

#include <laniakea/base.h>

#define LANIAKEA_PREFERENCES_CONFIG_PATH ".config/laniakea/preferences.conf"
#define LA_PREFERENCES_LANIAKEA_CONFIG_PATH ".config/laniakea.conf"

#define LANIAKEA_PREFERENCES_CAPS_LOCK_BEHAVIOR_CAPS_LOCK "CapsLock"
#define LANIAKEA_PREFERENCES_CAPS_LOCK_BEHAVIOR_CTRL "Ctrl"
#define LANIAKEA_PREFERENCES_CAPS_LOCK_BEHIVIOR_ESC "Esc"

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
    // char *wallpapers;        // Future feature.
    // size_t number_of_desktops;
    // - Keyboard.
    // char *caps_lock_behavior;   // ["CapsLock", "Ctrl", "Esc"]
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


/**
 * @brief Save config file to disk.
 *
 * @param preferences The laniakea_preferences object.
 * @return Error code.
 */
int laniakea_preferences_save(laniakea_preferences *preferences);


/**
 * @brief Free preferences from memory.
 *
 * @param preferences The laniakea_preferences object.
 */
void laniakea_preferences_free(laniakea_preferences *preferences);


/*====================*/
/* Appearance get/set */
/*====================*/

laniakea_bool laniakea_preferences_dark_mode(laniakea_preferences *preferences);

void laniakea_preferences_set_dark_mode(laniakea_preferences *preferences,
        laniakea_bool value);

bool laniakea_preferences_appearance_dark_mode(
        laniakea_preferences *preferences);

void laniakea_preferences_appearance_set_dark_mode(
        laniakea_preferences *preferences, bool value);

/*=================*/
/* Display get/set */
/*=================*/


/*=================*/
/* Desktop get/set */
/*=================*/

const char* laniakea_preferences_desktop_wallpaper(
        laniakea_preferences *preferences);

void laniakea_preferences_desktop_set_wallpaper(
        laniakea_preferences *preferences, const char *path);


/*==================*/
/* Keyboard get/set */
/*==================*/

const char* laniakea_preferences_keyboard_caps_lock_behavior(
        laniakea_preferences *preferences);

void laniakea_preferences_set_keyboard_caps_lock_behavior(
        laniakea_preferences *preferences, const char *behavior);


uint16_t laniakea_preferences_keyboard_delay_until_repeat(
        laniakea_preferences *preferences);


void laniakea_preferences_set_keyboard_delay_until_repeat(
        laniakea_preferences *preferences, uint16_t value
);

uint8_t laniakea_preferences_keyboard_key_repeat(
        laniakea_preferences *preferences
);

void laniakea_preferences_set_keyboard_key_repeat(
        laniakea_preferences *preferences, uint8_t value
);


LANIAKEA_EXTERN_C_END

#endif /* _LANIAKEA_PREFERENCES_H */
