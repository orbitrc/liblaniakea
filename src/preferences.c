#include <laniakea/preferences.h>

// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// POSIX
#include <sys/types.h>

#include <laniakea/base.h>
#include <laniakea/ini.h>
#include <laniakea/string.h>

LA_EXTERN_C_BEGIN

la_preferences* la_preferences_new()
{
    la_preferences *preferences = malloc(sizeof(la_preferences));

    preferences->conf = NULL;

    return preferences;
}

int la_preferences_load(la_preferences *preferences)
{
    // Initialize ini.
    if (preferences->conf == NULL) {
        preferences->conf = la_ini_new();
    }

    // Make path.
    const char *home = getenv("HOME");
    char *path = malloc(
        strlen(home) + strlen(LA_PREFERENCES_LANIAKEA_CONFIG_PATH) + 2);
    strncpy(path, home, strlen(home));
    path[strlen(home)] = '\0';
    strncat(path, "/", 2);
    strncat(path,
        LA_PREFERENCES_LANIAKEA_CONFIG_PATH,
        strlen(LA_PREFERENCES_LANIAKEA_CONFIG_PATH) + 1);

    // Load file.
    int err = la_ini_load(preferences->conf, path);
    if (err == LA_FILE_ERROR_NO_FILE) {
        return err;
    }
    if (err != LA_FILE_ERROR_SUCCESS) {
        return err;
    }

    return LA_FILE_ERROR_SUCCESS;
}

int la_preferences_save(la_preferences *preferences)
{
    // Make path.
    const char *home = getenv("HOME");
    char *path = malloc(
        strlen(home) + strlen(LA_PREFERENCES_LANIAKEA_CONFIG_PATH) + 2);
    strncpy(path, home, strlen(home));
    strncat(path, "/", 2);
    strncat(path,
        LA_PREFERENCES_LANIAKEA_CONFIG_PATH,
        strlen(LA_PREFERENCES_LANIAKEA_CONFIG_PATH) + 1);
    int err = la_ini_save(preferences->conf, path);
    free(path);

    // Save file.
    if (err == LA_FILE_ERROR_NO_DIRECTORY) {
        return err;
    }
    if (err == LA_FILE_ERROR_PERMISSION) {
        return err;
    }
    if (err != LA_FILE_ERROR_SUCCESS) {
        return err;
    }

    return LA_FILE_ERROR_SUCCESS;
}

void la_preferences_free(la_preferences *preferences)
{
    la_ini_free(preferences->conf);
    free(preferences);
}

/*====================*/
/* Appearance get/set */
/*====================*/

bool la_preferences_appearance_dark_mode(
        la_preferences *preferences)
{
    int err;
    bool value = la_ini_get_bool(preferences->conf,
        "appearance", "dark_mode", &err);

    // Set default value.
    const char *v = (value == true ? "true" : "false");
    if (err == LA_INI_GET_ERROR_NO_SECTION ||
            err == LA_INI_GET_ERROR_NO_KEY) {
        la_ini_insert(preferences->conf, "appearance", "dark_mode",
            v);

        return false;
    }

    return value;
}

void la_preferences_appearance_set_dark_mode(
        la_preferences *preferences, bool value)
{
    const char *v = (value == true ? "true" : "false");
    la_ini_insert(preferences->conf, "appearance", "dark_mode", v);
}

/*=================*/
/* Desktop get/set */
/*=================*/

const char* la_preferences_desktop_wallpaper(
        la_preferences *preferences)
{
    int err;
    const char *wallpaper = la_ini_get_string(preferences->conf,
        "desktop", "wallpaper", &err);

    if (err == LA_INI_GET_ERROR_NO_SECTION ||
            err == LA_INI_GET_ERROR_NO_KEY) {
        return "";
    }

    return wallpaper;
}

void la_preferences_desktop_set_wallpaper(
        la_preferences *preferences, const char *path)
{
    la_ini_insert(preferences->conf, "desktop", "wallpaper", path);
}

size_t la_preferences_desktop_number_of_desktops(la_preferences *preferences)
{
    int err;
    uint32_t value = la_ini_get_u32(preferences->conf,
        "desktop", "number_of_desktops", &err);

    if (err == LA_INI_GET_ERROR_NO_SECTION ||
            err == LA_INI_GET_ERROR_NO_KEY) {
        return LA_PREFERENCES_DEFAULT_DESKTOP_NUMBER_OF_DESKTOPS;
    }

    return (size_t)value;
}

void la_preferences_desktop_set_number_of_desktops(la_preferences *preferences,
        size_t value)
{
    char v[7];
    sprintf(v, "%lu", value);
    la_ini_insert(preferences->conf, "desktop", "number_of_desktops", v);
}

/*==================*/
/* Keyboard get/set */
/*==================*/

const char* la_preferences_keyboard_caps_lock_behavior(
        la_preferences *preferences
)
{
    int err;
    const char *value = la_ini_get_string(preferences->conf,
        "keyboard", "caps_lock_behavior", &err);

    // Set default value.
    if (value == NULL) {
        la_ini_insert(preferences->conf, "keyboard", "caps_lock_behavior",
            LA_PREFERENCES_CAPS_LOCK_BEHAVIOR_CAPS_LOCK);

        return LA_PREFERENCES_CAPS_LOCK_BEHAVIOR_CAPS_LOCK;
    }

    return value;
}

void la_preferences_set_keyboard_caps_lock_behavior(
        la_preferences *preferences, const char *behavior)
{
    la_ini_insert(preferences->conf, "keyboard", "caps_lock_behavior",
        behavior);
}

uint16_t la_preferences_keyboard_delay_until_repeat(
        la_preferences *preferences
)
{
    int err;
    char v[7];
    uint16_t value = la_ini_get_u32(preferences->conf,
        "keyboard", "delay_until_repeat", &err);

    // Set default value.
    if (err == LA_INI_GET_ERROR_NO_SECTION || err == LA_INI_GET_ERROR_NO_KEY) {
        sprintf(v, "%d",
            LA_PREFERENCES_DEFAULT_KEYBOARD_DELAY_UNTIL_REPEAT);
        la_ini_insert(preferences->conf, "keyboard", "delay_until_repeat",
            v);

        return LA_PREFERENCES_DEFAULT_KEYBOARD_DELAY_UNTIL_REPEAT;
    }

    return value;
}

void la_preferences_set_keyboard_delay_until_repeat(
        la_preferences *preferences, uint16_t value
)
{
    char v[7];
    sprintf(v, "%d", value);
    la_ini_insert(preferences->conf, "keyboard", "delay_until_repeat", v);
}

uint8_t la_preferences_keyboard_key_repeat(la_preferences *preferences)
{
    int err;
    char v[4];
    uint8_t value = la_ini_get_u32(preferences->conf, "keyboard",
        "key_repeat", &err);

    // Set default value.
    if (err == LA_INI_GET_ERROR_NO_SECTION || err == LA_INI_GET_ERROR_NO_KEY) {
        sprintf(v, "%d", LA_PREFERENCES_DEFAULT_KEYBOARD_KEY_REPEAT);
        la_ini_insert(preferences->conf, "keyboard", "key_repeat", v);

        return LA_PREFERENCES_DEFAULT_KEYBOARD_KEY_REPEAT;
    }

    return value;
}

void la_preferences_set_keyboard_key_repeat(
        la_preferences *preferences, uint8_t value
)
{
    char v[4];
    sprintf(v, "%d", value);
    la_ini_insert(preferences->conf, "keyboard", "key_repeat", v);
}


LA_EXTERN_C_END
