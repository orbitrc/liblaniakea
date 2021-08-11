#include <assert.h>
#include <stdio.h>

#include <laniakea/string.h>
#include <laniakea/vec.h>

void test_find()
{
    const char *str1 = "Hello world!";
    ssize_t index1 = la_string_find(str1, "world");
    printf("found index: %ld\n", index1);
    printf("string: %s\n", str1 + index1);

    const char *str2 = "Lorem ipsum";
    ssize_t index2 = la_string_find(str2, "-");
    assert(index2 == -1);
}

void test_splitn()
{
    const char *str1 = "My name is Yujeonja";
    la_string_vec *split1 = la_string_splitn(str1, 3, " ");
    for (size_t i = 0; i < split1->length; ++i) {
        printf("\"%s\"\n", la_string_vec_get(split1, i));
    }
    la_string_vec_free(split1);
    printf("-------------------------------\n");

    const char *str2 = "zero-length-split";
    la_string_vec *split2 = la_string_splitn(str2, 0, " ");
    for (size_t i = 0; i < split2->length; ++i) {
        printf("\"%s\"\n", la_string_vec_get(split2, i));
    }
    la_string_vec_free(split2);
    printf("-------------------------------\n");

    const char *str3 = "";
    la_string_vec *split3 = la_string_splitn(str3, 1, "X");
    for (size_t i = 0; i < split3->length; ++i) {
        printf("\"%s\"\n", la_string_vec_get(split3, i));
    }
    la_string_vec_free(split3);
    printf("-------------------------------\n");
}

void test_trim()
{
    char str1[32] = "Hello, world!     \n";
    la_string_trim(str1);
    assert(la_string_eq(str1, "Hello, world!"));

    char str2[32] = "[Item 42]\n";
    la_string_trim(str2);
    assert(la_string_eq(str2, "[Item 42]"));
}

void test_strip()
{
    char str[32] = "[Section name]";
    // Strip prefix.
    la_string_strip_prefix(str, "[");
    printf("stripped: %s\n", str);

    // Strip suffix.
    la_string_strip_suffix(str, "]");
    printf("stripped: %s\n", str);
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
    la_string_vec *split1 = la_string_split(str1, "::");
    for (size_t i = 0; i < split1->length; ++i) {
        printf("\"%s\"\n", la_string_vec_get(split1, i));
    }
    la_string_vec_free(split1);

    printf("------------------------\n");

    const char delim2[2] = "/";
    const char *str2 = "aa//b/c";
    la_string_vec *split2 = la_string_split(str2, delim2);
    for (size_t i = 0; i < split2->length; ++i) {
        printf("\"%s\"\n", la_string_vec_get(split2, i));
    }
    la_string_vec_free(split2);

    printf("------------------------\n");

    const char *str3 = ";;three;four;;";
    la_string_vec *split3 = la_string_split(str3, ";");
    for (size_t i = 0; i < split3-> length; ++i) {
        printf("\"%s\"\n", la_string_vec_get(split3, i));
    }
    la_string_vec_free(split3);

    printf("\n");

    printf("test_splitn\n");
    printf("=================\n");
    test_splitn();
    printf("\n");

    printf("test_trim\n");
    printf("==============\n");
    test_trim();
    printf("\n");

    printf("test ends_with\n");
    printf("=================\n");
    assert(la_string_ends_with("Foo bar", " bar"));
    printf("\n");

    printf("test_strip\n");
    printf("==============\n");
    test_strip();
    printf("\n");

    return 0;
}
