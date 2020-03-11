#include "ush.h"

int mx_sh_cd(char **args);
int mx_sh_help();
int mx_sh_exit();

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &mx_sh_cd,
    &mx_sh_help,
    &mx_sh_exit
};

int mx_sh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

int mx_sh_cd(char **args) {
    if (args[1] == NULL)
        fprintf(stderr, "ush: expected argument to \"cd\"\n");
    else
        if (chdir(args[1]) != 0)
            perror("ush");
    return 1;
}

int mx_sh_help() {
    int i;

    printf("Stephen Brennan's USH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");
    for (i = 0; i < mx_sh_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }
    printf("Use the man command for information on other programs.\n");
    return 1;
}

int mx_sh_exit() {
    return 0;
}

int mx_sh_launch(char **args) {
    pid_t pid;
    pid_t wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("ush");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("ush");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int mx_sh_execute(char **args) {
    int i;

    if (args[0] == NULL) {
        return 1;
    }
    for (i = 0; i < mx_sh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return mx_sh_launch(args);
}

char *mx_sh_read_line(void) {
    int bufsize = USH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "ush: allocation error\n");
        exit(EXIT_FAILURE);
    }
    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;
        if (position >= bufsize) {
            bufsize += USH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "ush: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **mx_sh_split_line(char *line) {
    int bufsize = USH_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "ush: allocation error\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(line, USH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;
        if (position >= bufsize) {
        bufsize += USH_TOK_BUFSIZE;
        tokens = realloc(tokens, bufsize * sizeof(char*));
        if (!tokens) {
                fprintf(stderr, "ush: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, USH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

void mx_sh_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("u$h> ");
        line = mx_sh_read_line();
        mx_check_args(line);
        args = mx_sh_split_line(line);
        status = mx_sh_execute(args);
        free(line);
        free(args);
    }
    while (status);
}

int main(int argc, char **argv) {
    argc = 0;
    argv = NULL;
    mx_sh_loop();
    return EXIT_SUCCESS;
}
