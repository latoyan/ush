#include "libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    char *str_1;
    char *str_2;
    char *concatenated_str;

    if (!s1 && !s2)
        return NULL;
    if (!s1)
        return mx_strdup(s2);
    if (!s2)
        return mx_strdup(s1);
    str_1 = mx_strdup(s1);
    str_2 = mx_strdup(s2);
    concatenated_str = mx_strcat(str_1, str_2);
    if (concatenated_str == NULL) {
        return NULL;
    }
    return concatenated_str;
}
