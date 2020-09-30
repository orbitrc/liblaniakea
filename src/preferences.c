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

LANIAKEA_EXTERN_C_BEGIN

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
        preferences->conf = laniakea_ini_new();
    }

    // Make path.
    const char *home = getenv("HOME");
    char *path = malloc(
        strlen(home) + strlen(LANIAKEA_PREFERENCES_CONFIG_PATH) + 2);
    strncpy(path, home, strlen(home));
    path[strlen(home)] = '\0';
    strncat(path, "/", 2);
    strncat(path,
        LANIAKEA_PREFERENCES_CONFIG_PATH,
        strlen(LANIAKEA_PREFERENCES_CONFIG_PATH) + 1);

    // Load file.
    int err = laniakea_ini_load(preferences->conf, path);
    if (err == LANIAKEA_FILE_ERROR_NO_FILE) {
        return err;
    }
    if (err != LANIAKEA_FILE_ERROR_SUCCESS) {
        return err;
    }

    return LANIAKEA_FILE_ERROR_SUCCESS;
}

int laniakea_preferences_save(laniakea_preferences *preferences)
{
    // Make path.
    const char *home = getenv("HOME");
    char *path = malloc(
        strlen(home) + strlen(LANIAKEA_PREFERENCES_CONFIG_PATH) + 2);
    strncpy(path, home, strlen(home));
    strncat(path, "/", 2);
    strncat(path,
        LANIAKEA_PREFERENCES_CONFIG_PATH,
        strlen(LANIAKEA_PREFERENCES_CONFIG_PATH) + 1);
    int err = laniakea_ini_save(preferences->conf, path);
    free(path);

    // Save file.
    if (err == LANIAKEA_FILE_ERROR_NO_DIRECTORY) {
        return err;
    }
    if (err == LANIAKEA_FILE_ERROR_PERMISSION) {
        return err;
    }
    if (err != LANIAKEA_FILE_ERROR_SUCCESS) {
        return err;
    }

    return LANIAKEA_FILE_ERROR_SUCCESS;
}

void laniakea_preferences_free(laniakea_preferences *preferences)
{
    laniakea_ini_free(preferences->conf);
    free(preferences);
}

laniakea_bool laniakea_preferences_dark_mode(laniakea_preferences *preferences)
{
    int err;
    laniakea_bool value = laniakea_ini_get_bool(preferences->conf,
        "Appearance", "dark_mode", &err);

    // Set default value.
    const char *v = (value == LANIAKEA_TRUE ? "true" : "false");
    if (err == LANIAKEA_INI_GET_ERROR_NO_SECTION ||
            err == LANIAKEA_INI_GET_ERROR_NO_KEY) {
        laniakea_ini_insert(preferences->conf, "Appearance", "dark_mode",
            v);

        return LANIAKEA_FALSE;
    }

    return value;
}

void laniakea_preferences_set_dark_mode(laniakea_preferences *preferences,
        laniakea_bool value)
{
    const char *v = (value == LANIAKEA_TRUE ? "true" : "false");
    laniakea_ini_insert(preferences->conf, "Appearance", "dark_mode", v);
}

/*=================*/
/* Desktop get/set */
/*=================*/

const char* laniakea_preferences_desktop_wallpaper(
        laniakea_preferences *preferences)
{
    int err;
    const char *wallpaper = laniakea_ini_get_string(preferences->conf,
        "Desktop", "wallpaper", &err);

    if (err == LANIAKEA_INI_GET_ERROR_NO_SECTION ||
            err == LANIAKEA_INI_GET_ERROR_NO_KEY) {
        return "";
    }

    return wallpaper;
}

void laniakea_preferences_desktop_set_wallpaper(
        laniakea_preferences *preferences, const char *path)
{
    laniakea_ini_insert(preferences->conf, "Desktop", "wallpaper", path);
}

/*==================*/
/* Keyboard get/set */
/*==================*/

const char* laniakea_preferences_keyboard_caps_lock_behavior(
        laniakea_preferences *preferences
)
{
    int err;
    const char *value = laniakea_ini_get_string(preferences->conf,
        "Keyboard", "caps_lock_behavior", &err);

    // Set default value.
    if (value == NULL) {
        laniakea_ini_insert(preferences->conf, "Keyboard", "caps_lock_behavior",
            LANIAKEA_PREFERENCES_CAPS_LOCK_BEHAVIOR_CAPS_LOCK);

        return LANIAKEA_PREFERENCES_CAPS_LOCK_BEHAVIOR_CAPS_LOCK;
    }

    return value;
}

void laniakea_preferences_set_keyboard_caps_lock_behavior(
        laniakea_preferences *preferences, const char *behavior)
{
    laniakea_ini_insert(preferences->conf, "Keyboard", "caps_lock_behavior",
        behavior);
}

uint16_t laniakea_preferences_keyboard_delay_until_repeat(
        laniakea_preferences *preferences
)
{
    int err;
    char v[7];
    uint16_t value = laniakea_ini_get_u32(preferences->conf,
        "Keyboard", "delay_until_repeat", &err);

    // Set default value.
    if (err == LANIAKEA_INI_GET_ERROR_NO_SECTION ||
            err == LANIAKEA_INI_GET_ERROR_NO_KEY) {
        sprintf(v, "%d",
            LANIAKEA_PREFERENCES_DEFAULT_KEYBOARD_DELAY_UNTIL_REPEAT);
        laniakea_ini_insert(preferences->conf, "Keyboard", "delay_until_repeat",
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
    laniakea_ini_insert(preferences->conf, "Keyboard", "delay_until_repeat", v);
}

uint8_t laniakea_preferences_keyboard_key_repeat(
        laniakea_preferences *preferences
)
{
    int err;
    char v[4];
    uint8_t value = laniakea_ini_get_u32(preferences->conf, "Keyboard",
        "key_repeat", &err);

    // Set default value.
    if (err == LANIAKEA_INI_GET_ERROR_NO_SECTION ||
            err == LANIAKEA_INI_GET_ERROR_NO_KEY) {
        sprintf(v, "%d", LANIAKEA_PREFERENCES_DEFAULT_KEYBOARD_KEY_REPEAT);
        laniakea_ini_insert(preferences->conf, "Keyboard", "key_repeat", v);

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
    laniakea_ini_insert(preferences->conf, "Keyboard", "key_repeat", v);
}


LANIAKEA_EXTERN_C_END
