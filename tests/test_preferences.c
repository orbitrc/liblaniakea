#include <laniakea/preferences.h>

int main()
{
    laniakea_preferences *preferences;
    preferences = laniakea_preferences_new();

    int err = laniakea_preferences_load(preferences);

    return 0;
}

