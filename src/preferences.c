#include <laniakea/preferences.h>

// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// POSIX
#include <sys/types.h>

LANIAKEA_EXTERN_C_BEGIN

laniakea_preferences* laniakea_preferences_new()
{
    laniakea_preferences *preferences = malloc(sizeof(laniakea_preferences));

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

    // Open file.
    FILE *f = fopen(path, "r");
    free(path);

    char *line;
    size_t buf_n = 0;
    ssize_t read_n = 0;

    while (read_n != -1) {
        read_n = getline(&line, &buf_n, f);
        printf("%d\n", read_n);
        if (read_n != -1) {
            printf("%s\n", line);
        }
    }
}

LANIAKEA_EXTERN_C_END