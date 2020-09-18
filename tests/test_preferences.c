#include <stdio.h>

#include <laniakea/preferences.h>

int main()
{
    laniakea_preferences *preferences;
    preferences = laniakea_preferences_new();

    int err = laniakea_preferences_load(preferences);
    if (err != LANIAKEA_FILE_ERROR_SUCCESS) {
        fprintf(stderr, "Error: %d\n", err);
    }
    laniakea_bool dark_mode = laniakea_preferences_dark_mode(preferences);

    return 0;
}

