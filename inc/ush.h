#ifndef USH_HEADER_H
#define USH_HEADER_H

#define USH_TOK_BUFSIZE 64
#define USH_TOK_DELIM " \t\r\n\a"
#define USH_RL_BUFSIZE 1024

#include "libmx.h"
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <dirent.h>
#include "string.h"
#include <signal.h>
#include <sys/wait.h>
#include <spawn.h>

void mx_check_args(char *line);
// int mx_sh_launch(char **args);
// void mx_sh_loop(void);
// char *mx_sh_read_line(void);
// char **mx_sh_split_line(char *line);
// int mx_sh_execute(char **args);

#endif
