#include <stdio.h>

#include <laniakea/preferences.h>

int main()
{
    la_preferences *preferences;
    preferences = la_preferences_new();

    int err = la_preferences_load(preferences);
    if (err != LA_FILE_ERROR_SUCCESS) {
        fprintf(stderr, "Error: %d\n", err);
    }
    bool dark_mode = la_preferences_appearance_dark_mode(preferences);
    fprintf(stderr, "dark_mode: %d\n", dark_mode);

    const char *wallpaper = la_preferences_desktop_wallpaper(preferences);
    fprintf(stderr, "wallpaper: %s\n", wallpaper);

    const char *caps_lock_behavior =
        la_preferences_keyboard_caps_lock_behavior(preferences);
    fprintf(stderr, "caps_lock_behavior: %s\n", caps_lock_behavior);

    // Reload test.
    printf("Test reload\n");
    printf("=================\n");
    fprintf(stderr, "1st free\n");
    la_preferences_free(preferences);
    fprintf(stderr, "1st new\n");
    preferences = la_preferences_new();
    fprintf(stderr, "1st load\n");
    err = la_preferences_load(preferences);
    fprintf(stderr, "1st err: %d\n", err);

    fprintf(stderr, "2nd free\n");
    la_preferences_free(preferences);
    fprintf(stderr, "2nd new\n");
    preferences = la_preferences_new();
    fprintf(stderr, "2nd load\n");
    err = la_preferences_load(preferences);
    fprintf(stderr, "2nd err: %d\n", err);
    fprintf(stderr, "2nd reloaded.\n");

    fprintf(stderr, "freeing...\n");
    fprintf(stderr, "preferences->conf: %p\n", preferences->conf);
    la_preferences_free(preferences);

    fprintf(stderr, "done.\n");

    return 0;
}

