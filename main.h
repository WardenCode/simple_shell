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

/**
 * struct response - Struct to translate the tokens and holder
 *
 * @toks: Double pointer to the tokens.
 *
 * @hold: Pointer to a token to free later.
 */

typedef struct response
{
	char **toks;
	char *hold;
} response;

/**
 * struct built - Struct to translate the tokens and holder
 *
 * @key: Pointer to a key (name of the built).
 *
 * @hold: Pointer to a function of the built.
 */

typedef struct built
{
	char *key;
	int (*func)(response *res);
} built;

extern char **environ;

/* Shell Functions */
char *find_char_rev(char *str, char character);
char *no_new_line(char *command, char *new_command);
char *only_the_command(char *cmd);
void do_the_command(response *res);
void free_tokens(char **tokens);

/* Shell Functions 2*/
int all_spaces(char *command, ssize_t size);
int total_malloc(char *command);
response *tokenize(char *input);
int first_validations(char *command, int bytes_read);
void validate_last_access(response *res, char *file, int *errors);

/* Shell Functions 3*/
int route_works(response *obj, int *while_status);
void free_all(response *obj, int *while_status);
int fail_route(response *req, char *argv, int *err);
char *clean_spaces(char *command);

/* Utils */
char *str_concat(char *s1, char *s2);
void print_list(const path_dir_t *node);
char *find_char(char *key, char character);
char *validate_slash(char *cmd, char *holder);
char *which(char *command);

/*Built in Functions*/
int built_env(response *res __attribute__ ((unused)));
int built_exit(response *res);
int built_cd(response *res __attribute__ ((unused)));
int built_help(response *res __attribute__ ((unused)));
int built_alias(response *res __attribute__ ((unused)));
int built_setenv(response *res __attribute__ ((unused)));
int built_unsetenv(response *res __attribute__ ((unused)));

/*Built in Utils*/
char *find_points(char *key);

/* Prototypes */
void display_path(void);
path_dir_t *linked_path(void);
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

#endif
