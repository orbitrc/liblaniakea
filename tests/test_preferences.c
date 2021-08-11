#include <stdio.h>

#include <laniakea/preferences.h>

int main()
{
    laniakea_preferences *preferences;
    preferences = laniakea_preferences_new();

    int err = laniakea_preferences_load(preferences);
    if (err != LA_FILE_ERROR_SUCCESS) {
        fprintf(stderr, "Error: %d\n", err);
    }
    bool dark_mode = laniakea_preferences_dark_mode(preferences);
    fprintf(stderr, "dark_mode: %d\n", dark_mode);

    const char *wallpaper = laniakea_preferences_desktop_wallpaper(preferences);
    fprintf(stderr, "wallpaper: %s\n", wallpaper);

    const char *caps_lock_behavior =
        laniakea_preferences_keyboard_caps_lock_behavior(preferences);
    fprintf(stderr, "caps_lock_behavior: %s\n", caps_lock_behavior);

    // Reload test.
    printf("Test reload\n");
    printf("=================\n");
    fprintf(stderr, "1st free\n");
    laniakea_preferences_free(preferences);
    fprintf(stderr, "1st new\n");
    preferences = laniakea_preferences_new();
    fprintf(stderr, "1st load\n");
    err = laniakea_preferences_load(preferences);
    fprintf(stderr, "1st err: %d\n", err);

    fprintf(stderr, "2nd free\n");
    laniakea_preferences_free(preferences);
    fprintf(stderr, "2nd new\n");
    preferences = laniakea_preferences_new();
    fprintf(stderr, "2nd load\n");
    err = laniakea_preferences_load(preferences);
    fprintf(stderr, "2nd err: %d\n", err);
    fprintf(stderr, "2nd reloaded.\n");

    fprintf(stderr, "freeing...\n");
    fprintf(stderr, "preferences->conf: %p\n", preferences->conf);
    laniakea_preferences_free(preferences);

    fprintf(stderr, "done.\n");

    return 0;
}

