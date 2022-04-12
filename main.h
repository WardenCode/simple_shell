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
	int (*func)(response *r, int *err, char *av, int *exit_status);
} built;

extern char **environ;

/* Shell Functions */
char *only_the_command(char *cmd);
void free_tokens(char **tokens);
void do_the_command(response *res, int *exit_status);
int all_spaces(char *command, ssize_t size);
int total_malloc(char *command);

/* Shell Functions 2*/
response *tokenize(char *input);
int first_validations(char *command, int bytes_read, int *while_st);
void validate_last_access(response *r, char *file, int *err, int *exit_status);
int route_works(response *obj, int *while_status, int *exit_status);
void free_all(response *obj, int *while_status);

/* Shell Functions 3*/
int fail_route(response *r, char *av, int *err, int *exit_status);
char *clean_spaces(char *command);
char *which(char *command);

/* Utils */
char *validate_slash(char *cmd, char *holder);
char *find_char(char *key, char character);
void display_path(void);
char *str_concat(char *s1, char *s2);

/*Built in Functions*/
int match_built_in(response *r, int *err, char *av, int *exit_status);
int built_env(response *r, int *err, char *av, int *exit_status);
int built_exit(response *r, int *err, char *av, int *exit_status);
int built_setenv(response *r, int *err, char *av, int *exit_status);
int built_unsetenv(response *r, int *err, char *av, int *exit_status);
int built_cd(response *r, int *err, char *av, int *exit_status);
int built_help(response *r, int *err, char *av, int *exit_status);

/*Future releases*/
int built_alias(response *r, int *err, char *av, int *exit_status);

/*Built in Utils*/
void c_handler(int x);
int number_of_tokens(char **tokens);
char *find_points(char *key);
int is_number(char *str);

#endif
