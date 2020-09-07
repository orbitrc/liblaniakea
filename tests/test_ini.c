#include <stdio.h>

#include <laniakea/ini.h>

void test_insert()
{
    laniakea_ini *ini = laniakea_ini_new();
    laniakea_ini_insert(ini, "Section 1", "key1", "value1");
    laniakea_ini_insert(ini, "Section 1", "key2", "value2");
    laniakea_ini_insert(ini, "Section 2", "key1", "value1");
    laniakea_ini_insert(ini, "Section 2", "key2", "value2");

    laniakea_ini_free(ini);
}

int main()
{
    //================
    // Test insert
    //================
    printf("test insert.\n");
    printf("==============\n");
    test_insert();
    printf("\n");
    
    //================
    // Test load
    //================
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