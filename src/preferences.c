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

laniakea_preferences* laniakea_preferences_new()
{
    laniakea_preferences *preferences = malloc(sizeof(laniakea_preferences));

    preferences->conf = NULL;

    return preferences;
}

int laniakea_preferences_load(laniakea_preferences *preferences)
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

int laniakea_preferences_save(laniakea_preferences *preferences)
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

void laniakea_preferences_free(laniakea_preferences *preferences)
{
    la_ini_free(preferences->conf);
    free(preferences);
}

/*====================*/
/* Appearance get/set */
/*====================*/

bool laniakea_preferences_appearance_dark_mode(
        laniakea_preferences *preferences)
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

void laniakea_preferences_appearance_set_dark_mode(
        laniakea_preferences *preferences, bool value)
{
    const char *v = (value == true ? "true" : "false");
    la_ini_insert(preferences->conf, "appearance", "dark_mode", v);
}

// Deprecated
bool laniakea_preferences_dark_mode(laniakea_preferences *preferences)
{
    fprintf(stderr, "laniakea_preferences_dark_mode() is deprecated. ");
    fprintf(stderr, "Use laniakea_preferences_appearance_dark_mode().\n");
    return laniakea_preferences_appearance_dark_mode(preferences);
}

// Deprecated
void laniakea_preferences_set_dark_mode(laniakea_preferences *preferences,
        bool value)
{
    fprintf(stderr, "laniakea_preferences_set_dark_mode() is deprecated. ");
    fprintf(stderr, "Use laniakea_preferences_appearance_set_dark_mode().\n");
    return laniakea_preferences_appearance_set_dark_mode(preferences, value);
}

/*=================*/
/* Desktop get/set */
/*=================*/

const char* laniakea_preferences_desktop_wallpaper(
        laniakea_preferences *preferences)
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

void laniakea_preferences_desktop_set_wallpaper(
        laniakea_preferences *preferences, const char *path)
{
    la_ini_insert(preferences->conf, "desktop", "wallpaper", path);
}

/*==================*/
/* Keyboard get/set */
/*==================*/

const char* laniakea_preferences_keyboard_caps_lock_behavior(
        laniakea_preferences *preferences
)
{
    int err;
    const char *value = la_ini_get_string(preferences->conf,
        "keyboard", "caps_lock_behavior", &err);

    // Set default value.
    if (value == NULL) {
        la_ini_insert(preferences->conf, "keyboard", "caps_lock_behavior",
            LANIAKEA_PREFERENCES_CAPS_LOCK_BEHAVIOR_CAPS_LOCK);

        return LANIAKEA_PREFERENCES_CAPS_LOCK_BEHAVIOR_CAPS_LOCK;
    }

    return value;
}

void laniakea_preferences_set_keyboard_caps_lock_behavior(
        laniakea_preferences *preferences, const char *behavior)
{
    la_ini_insert(preferences->conf, "keyboard", "caps_lock_behavior",
        behavior);
}

uint16_t laniakea_preferences_keyboard_delay_until_repeat(
        laniakea_preferences *preferences
)
{
    int err;
    char v[7];
    uint16_t value = la_ini_get_u32(preferences->conf,
        "keyboard", "delay_until_repeat", &err);

    // Set default value.
    if (err == LA_INI_GET_ERROR_NO_SECTION ||
            err == LA_INI_GET_ERROR_NO_KEY) {
        sprintf(v, "%d",
            LANIAKEA_PREFERENCES_DEFAULT_KEYBOARD_DELAY_UNTIL_REPEAT);
        la_ini_insert(preferences->conf, "keyboard", "delay_until_repeat",
            v);

        return LANIAKEA_PREFERENCES_DEFAULT_KEYBOARD_DELAY_UNTIL_REPEAT;
    }

    return value;
}

void laniakea_preferences_set_keyboard_delay_until_repeat(
        laniakea_preferences *preferences, uint16_t value
)
{
    char v[7];
    sprintf(v, "%d", value);
    la_ini_insert(preferences->conf, "keyboard", "delay_until_repeat", v);
}

uint8_t laniakea_preferences_keyboard_key_repeat(
        laniakea_preferences *preferences
)
{
    int err;
    char v[4];
    uint8_t value = la_ini_get_u32(preferences->conf, "keyboard",
        "key_repeat", &err);

    // Set default value.
    if (err == LA_INI_GET_ERROR_NO_SECTION ||
            err == LA_INI_GET_ERROR_NO_KEY) {
        sprintf(v, "%d", LANIAKEA_PREFERENCES_DEFAULT_KEYBOARD_KEY_REPEAT);
        la_ini_insert(preferences->conf, "keyboard", "key_repeat", v);

        return LANIAKEA_PREFERENCES_DEFAULT_KEYBOARD_KEY_REPEAT;
    }

    return value;
}

void laniakea_preferences_set_keyboard_key_repeat(
        laniakea_preferences *preferences, uint8_t value
)
{
    char v[4];
    sprintf(v, "%d", value);
    la_ini_insert(preferences->conf, "keyboard", "key_repeat", v);
}


LA_EXTERN_C_END
