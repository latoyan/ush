#include "libmx.h"

char *mx_strdup(const char *s1) {
    int len = mx_strlen(s1);
    char *target = mx_strnew(len);

    for (int i = 0; i < len; i++) {
        target[i] = s1[i];
        target[i + 1] = '\0';
    }
    return target;
}
