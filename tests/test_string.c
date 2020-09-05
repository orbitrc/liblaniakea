#include <laniakea/string.h>
#include <laniakea/vec.h>

int main()
{
    const char *str1 = "Hello::world::foo::bar";
    laniakea_string_vec *split1 = laniakea_string_split(str1, "::");
    for (size_t i = 0; i < split1->length; ++i) {
        printf("%s\n", laniakea_string_vec_get(split1, i));
    }
    laniakea_string_vec_free(split1);

    printf("=======================\n");

    const char *str2 = "aa//b/c";
    laniakea_string_vec *split2 = laniakea_string_split(str2, "/");
    for (size_t i = 0; i < split2->length; ++i) {
        printf("\"%s\"\n", laniakea_string_vec_get(split2, i));
    }
    laniakea_string_vec_free(split2);

    printf("=======================\n");

    const char *str3 = ";;three;four;";
    laniakea_string_vec *split3 = laniakea_string_split(str3, ";");
    for (size_t i = 0; i < split3-> length; ++i) {
        printf("\"%s\"\n", laniakea_string_vec_get(split3, i));
    }
    laniakea_string_vec_free(split3);

    return 0;
}