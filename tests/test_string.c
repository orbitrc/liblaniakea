#include <laniakea/string.h>
#include <laniakea/vec.h>

int main()
{
    const char *str1 = "Hello::world::foo::bar";
    laniakea_string_vec *split1 = laniakea_string_split(str1, "::");

    laniakea_string_vec_free(split1);
    
    return 0;
}