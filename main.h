#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * struct path_dir_t - Struct to use it in path linked list
 *
 * @dir: A char with some option
 *
 * @next: Pointer to the next node
 */

typedef struct path_dir_t
{
	char *dir;
	struct path_dir_t *next;
} path_dir_t;

extern char **environ;

/* Utils */
char *str_concat(char *s1, char *s2);
void print_list(const path_dir_t *node);
char *find_char(char *key, char character);
char *validate_slash (char *cmd, char *holder, char *final);
char *which(char *command);

/* Prototypes */
void display_path(void);
path_dir_t *linked_path(void);
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

#endif