#include <assert.h>
#include <stdio.h>

#include <laniakea/string.h>
#include <laniakea/vec.h>

void test_find()
{
    const char *str1 = "Hello world!";
    size_t index1 = laniakea_string_find(str1, "world");
    printf("found index: %ld\n", index1);
    printf("string: %s\n", str1 + index1);

    const char *str2 = "Lorem ipsum";
    size_t index2 = laniakea_string_find(str2, "-");
    assert(index2 == -1);
}

void test_splitn()
{
    const char *str1 = "My name is Yujeonja";
    laniakea_string_vec *split1 = laniakea_string_splitn(str1, 3, " ");
    for (size_t i = 0; i < split1->length; ++i) {
        printf("\"%s\"\n", laniakea_string_vec_get(split1, i));
    }
    laniakea_string_vec_free(split1);
    printf("-------------------------------\n");

    const char *str2 = "zero-length-split";
    laniakea_string_vec *split2 = laniakea_string_splitn(str2, 0, " ");
    for (size_t i = 0; i < split2->length; ++i) {
        printf("\"%s\"\n", laniakea_string_vec_get(split2, i));
    }
    laniakea_string_vec_free(split2);
    printf("-------------------------------\n");

    const char *str3 = "";
    laniakea_string_vec *split3 = laniakea_string_splitn(str3, 1, "X");
    for (size_t i = 0; i < split3->length; ++i) {
        printf("\"%s\"\n", laniakea_string_vec_get(split3, i));
    }
    laniakea_string_vec_free(split3);
    printf("-------------------------------\n");
}

int main()
{
    printf("test_find\n");
    printf("=============\n");
    test_find();
    printf("\n");

    printf("test_split\n");
    printf("===============\n");
    const char *str1 = "Hello::world::foo::bar::baz::fn";
    laniakea_string_vec *split1 = laniakea_string_split(str1, "::");
    for (size_t i = 0; i < split1->length; ++i) {
        printf("\"%s\"\n", laniakea_string_vec_get(split1, i));
    }
    laniakea_string_vec_free(split1);

    printf("------------------------\n");

    const char delim2[2] = "/";
    const char *str2 = "aa//b/c";
    laniakea_string_vec *split2 = laniakea_string_split(str2, delim2);
    for (size_t i = 0; i < split2->length; ++i) {
        printf("\"%s\"\n", laniakea_string_vec_get(split2, i));
    }
    laniakea_string_vec_free(split2);

    printf("------------------------\n");

    const char *str3 = ";;three;four;;";
    laniakea_string_vec *split3 = laniakea_string_split(str3, ";");
    for (size_t i = 0; i < split3-> length; ++i) {
        printf("\"%s\"\n", laniakea_string_vec_get(split3, i));
    }
    laniakea_string_vec_free(split3);

    printf("\n");

    printf("test_splitn\n");
    printf("=================\n");
    test_splitn();
    printf("\n");

    return 0;
}