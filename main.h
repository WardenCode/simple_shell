#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
/* MACROS */

#define UNUSED(x) (void)(x)

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
 * @func: Pointer to a function of the built.
 */

typedef struct built
{
	char *key;
	int (*func)(response *res, int *errors, char *argv);
} built;

extern char **environ;

/* Shell Functions */
char *only_the_command(char *cmd);
void free_tokens(char **tokens);
void do_the_command(response *res);
int all_spaces(char *command, ssize_t size);
int total_malloc(char *command);

/* Shell Functions 2*/
response *tokenize(char *input);
int first_validations(char *command, int bytes_read);
void validate_last_access(response *res, char *file, int *errors);
int route_works(response *obj, int *while_status);
void free_all(response *obj, int *while_status);

/* Shell Functions 3*/
int fail_route(response *req, char *argv, int *err);
char *clean_spaces(char *command);
char *which(char *command);

/* Utils */
char *validate_slash(char *cmd, char *holder);
char *find_char(char *key, char character);
void display_path(void);
char *str_concat(char *s1, char *s2);

/*Built in Functions*/
int match_built_in(response *res, int *errors, char *argv);
int built_env(response *res, int *errors, char *argv);
int built_exit(response *res, int *errors, char *argv);
int built_cd(response *res, int *errors, char *argv);
int built_help(response *res, int *errors, char *argv);

/*Future releases*/
int built_alias(response *res, int *errors, char *argv);
int built_setenv(response *res, int *errors, char *argv);
int built_unsetenv(response *res, int *errors, char *argv);

/*Built in Utils*/
void c_handler(int x);
int number_of_tokens(char **tokens);
char *find_points(char *key);
int is_number(char *str);

#endif
