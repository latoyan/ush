#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <xlocale.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <pwd.h>

void mx_printchar(char c);
void mx_printstr(const char *s);
void mx_print_strarr(char **arr, const char *delim);
void mx_printint(int n);
double mx_pow(double n, int pow);
int mx_sqrt(int x);
char *mx_itoa(int number);
void mx_foreach(int *arr, int size, void (*f)(int));
int mx_binary_search(char **arr, int size, const char *s, int *count);
int mx_bubble_sort(char **arr, int size);

void mx_intdel(int **num);
void mx_del_intarr(int ***num_arr);
int mx_atoi(const char *str);
int mx_strlen(const char *s);
void mx_swap_char(char *s1, char *s2);
void mx_str_reverse(char *s);
void mx_strdel(char **str);
void mx_del_strarr(char ***arr);
int mx_get_char_index(const char *str, char c);
char *mx_strdup(const char *s1);
char *mx_strndup(const char *s1, size_t n);
char *mx_strcpy(char *dst, const char *src);
char *mx_strncpy(char *dst, const char *src, int len);
int mx_strcmp(const char *s1, const char *s2);
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strstr(const char *haystack, const char *needle);
int mx_get_substr_index(const char *str, const char *sub);
int mx_count_substr(const char *str, const char *sub);
int mx_count_words(const char *str, char c);
char *mx_strnew(const int size);
char *mx_strtrim(const char *str);
char **mx_strsplit(const char *s, char c);
char *mx_strjoin(const char *s1, const char *s2);
char *mx_file_to_str(const char *file);
char *mx_replace_substr(const char *str, const char *sub, const char *replace);
char *mx_strchr(const char *s, int c);
int mx_strncmp(const char *s1, const char *s2, int n);

void *mx_memset(void *b, int c, size_t len);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
int mx_memcmp(const void *s1, const void *s2, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len);
void *mx_memmove(void *dst, const void *src, size_t len);

char *mx_echo(char *flags, char **params, char **env, int *exit_code);
char *mx_check_echof(char *flags, char *str);
char *mx_check_slashn(char *str, int *exit_code);

char *mx_echo(char *flags, char **params, char **env, int *exit) {
    char *str = NULL;

    for (int i = 0; params[i]; i++) {
        str = mx_strjoin(str, params[i]);
        if (params[i + 1] != NULL)
            str = mx_strjoin(str, " ");
    }
    str = mx_check_slashn(str, exit_code);
    if (flags != NULL)
        str = mx_check_echof(flags, str);
    else
        str = mx_strjoin(str, "\n");
    return str;
}

char *mx_check_slashn(char *str, int *exit_code) {
    char *restr = (char*)malloc(strlen(str));

    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n')
            restr[i] = ' ';
        else
            restr[i] = str[i];
    }
    return restr;
}

char *mx_check_echof(char *flags, char *str) {
    char *res = str;
    int count = 0;

    for (int i = 0; flags[i]; i++)
        if (flags[i] == 'n') {
            return res;
        }
    return res;
}

int main() {
    char *str = NULL;
    char *flags = "n";
    char *params[] = {"st\nr\ngtgrqqw qweqweq", "he\nllo","erferfn\ne ","T_T" , NULL};
    char **env = NULL;
    int exit_code = 0;

    str = mx_echo(flags, params, env, &exit_code);
    printf("%s", str);
    return 0;
}
