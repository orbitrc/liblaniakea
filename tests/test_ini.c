#include <stdio.h>

#include <laniakea/ini.h>

void test_section_insert()
{
    la_ini_section *sec = la_ini_section_new("Section 1");

    la_ini_section_insert(sec, "key1", "value1");
    la_ini_section_insert(sec, "key2", "value2");

    la_ini_section_free(sec);
}

void test_insert()
{
    la_ini *ini = la_ini_new();
    la_ini_insert(ini, "Section 1", "key1", "value1");
    la_ini_insert(ini, "Section 1", "key2", "value2");
    la_ini_insert(ini, "Section 2", "key1", "value1");
    la_ini_insert(ini, "Section 2", "key2", "value2");
    la_ini_insert(ini, "Section 3", "key1", "value1");
    la_ini_insert(ini, "Section 4", "key1", "value1");

    la_ini_free(ini);
}

int main()
{
    //======================
    // Test section insert
    //======================
    printf("test section insert.\n");
    printf("=====================\n");
    test_section_insert();
    printf("\n");

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
    printf("test load\n");
    printf("==============\n");
    la_ini *ini = la_ini_new();
    int err = la_ini_load(ini, "tests/test.ini");
    if (err != LA_FILE_ERROR_SUCCESS) {
        fprintf(stderr, "Failed to load ini file.\n");
        return 1;
    }
    printf("\n");

    //=================
    // Test reload
    //=================
    printf("test reload\n");
    printf("==================\n");
    la_ini_free(ini);
    ini = la_ini_new();
    la_ini_load(ini, "tests/test.ini");

    la_ini_free(ini);
    ini = la_ini_new();
    la_ini_load(ini, "tests/test.ini");
    printf("\n");

    //=================
    // Test save
    //=================
    printf("test save\n");
    printf("=============\n");
    err = la_ini_save(ini, "tests/save_test.ini");
    if (err != LA_FILE_ERROR_SUCCESS) {
        fprintf(stderr, "Failed to save ini file.\n");
        return 1;
    }

    // Free.
    la_ini_free(ini);

    return 0;
}
