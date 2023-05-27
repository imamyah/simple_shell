#ifndef SHELL_H
#define SHELL_H

/* libraries */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

/* ---------- */

/* declarations */
#define SIZE 1024
#define ARGS_SIZE 50

extern char **environ;

/*----------*/

/* functions*/
int _fork(char *args[], char *cmd);
void splitter(char *input, char *args[]);
char *read_cmd(void);
void nstr(int nr, char *str);
void comments(char *input);
void error(char *args[], int loops);
char *get_path(char *args[]);
int spaces(char *input);
void cd(char *args[]);
int builtins(char *args[]);

/* ---------- */

#endif
