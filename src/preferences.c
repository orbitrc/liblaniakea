#include <laniakea/preferences.h>

// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// POSIX
#include <sys/types.h>

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
    // Make path.
    const char *home = getenv("HOME");
    char *path = malloc(
        strlen(home) + strlen(LANIAKEA_PREFERENCES_CONFIG_PATH) + 2);
    strncpy(path, home, strlen(home));
    strncat(path, "/", 2);
    strncat(path,
        LANIAKEA_PREFERENCES_CONFIG_PATH,
        strlen(LANIAKEA_PREFERENCES_CONFIG_PATH) + 1);

    // Load file.
    preferences->conf = laniakea_ini_load(path);
    if (preferences->conf == NULL) {
        return LANIAKEA_ERROR_NO_SUCH_FILE;
    }

    return LANIAKEA_ERROR_SUCCESS;
}

LANIAKEA_EXTERN_C_END