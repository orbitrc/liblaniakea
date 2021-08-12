#ifndef _LANIAKEA_PREFERENCES_H
#define _LANIAKEA_PREFERENCES_H

#include <stdint.h>
#include <stdlib.h>

#include <laniakea/base.h>

#define LA_PREFERENCES_LANIAKEA_PREFERENCES_CONFIG_PATH ".config/laniakea/preferences.conf"
#define LA_PREFERENCES_LANIAKEA_CONFIG_PATH ".config/laniakea.conf"

#define LA_PREFERENCES_CAPS_LOCK_BEHAVIOR_CAPS_LOCK "CapsLock"
#define LA_PREFERENCES_CAPS_LOCK_BEHAVIOR_CTRL "Ctrl"
#define LA_PREFERENCES_CAPS_LOCK_BEHIVIOR_ESC "Esc"

#define LA_PREFERENCES_DEFAULT_DESKTOP_NUMBER_OF_DESKTOPS 4
#define LA_PREFERENCES_DEFAULT_KEYBOARD_DELAY_UNTIL_REPEAT 600
#define LA_PREFERENCES_DEFAULT_KEYBOARD_KEY_REPEAT 25
#define LA_PREFERENCES_DEFAULT_POWER_SHOW_BATTERY_IN_MENU_BAR true

LA_EXTERN_C_BEGIN

typedef struct la_ini la_ini;

typedef struct la_preferences {
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
    la_ini *conf;
} la_preferences;


/**
 * @brief Create new la_preferences object.
 *
 * @return Newly allocated la_preferences object.
 */
la_preferences* la_preferences_new();


/**
 * @brief Load config file from disk.
 * 
 * @param preferences The la_preferences object.
 * @return Error code.
 */
int la_preferences_load(la_preferences *preferences);


/**
 * @brief Save config file to disk.
 *
 * @param preferences The la_preferences object.
 * @return Error code.
 */
int la_preferences_save(la_preferences *preferences);


/**
 * @brief Free preferences from memory.
 *
 * @param preferences The la_preferences object.
 */
void la_preferences_free(la_preferences *preferences);


/*====================*/
/* Appearance get/set */
/*====================*/

bool la_preferences_appearance_dark_mode(
        la_preferences *preferences);

void la_preferences_appearance_set_dark_mode(
        la_preferences *preferences, bool value);

/*=================*/
/* Display get/set */
/*=================*/


/*=================*/
/* Desktop get/set */
/*=================*/

const char* la_preferences_desktop_wallpaper(
        la_preferences *preferences);

void la_preferences_desktop_set_wallpaper(
        la_preferences *preferences, const char *path);

size_t la_preferences_desktop_number_of_desktops(la_preferences *preferences);

void la_preferences_desktop_set_number_of_desktops(
        la_preferences *preferences, size_t value);

/*==================*/
/* Keyboard get/set */
/*==================*/

const char* la_preferences_keyboard_caps_lock_behavior(
        la_preferences *preferences);

void la_preferences_set_keyboard_caps_lock_behavior(
        la_preferences *preferences, const char *behavior);


uint16_t la_preferences_keyboard_delay_until_repeat(
        la_preferences *preferences);


void la_preferences_set_keyboard_delay_until_repeat(
        la_preferences *preferences, uint16_t value
);

uint8_t la_preferences_keyboard_key_repeat(
        la_preferences *preferences
);

void la_preferences_set_keyboard_key_repeat(
        la_preferences *preferences, uint8_t value
);


LA_EXTERN_C_END

#endif /* _LANIAKEA_PREFERENCES_H */
