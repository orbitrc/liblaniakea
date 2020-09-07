#include <stdio.h>

#include <laniakea/ini.h>

int main()
{
    laniakea_ini *ini = laniakea_ini_new();
    int err = laniakea_ini_load(ini, "tests/test.ini");
    if (err != LANIAKEA_FILE_ERROR_SUCCESS) {
        fprintf(stderr, "Failed to load ini file.\n");
        return 1;
    }

    // Free.
    laniakea_ini_free(ini);

    return 0;
}