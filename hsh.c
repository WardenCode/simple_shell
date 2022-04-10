#include "main.h"

/**
 * match_built_in - Find if the built in to use.
 *
 * @res: Pointer to the structure (tokens, holder).
 *
 * Return: Return 1 if use a function, 0 otherwise.
 */

/* int match_built_in(response *res) */
/* { */
/* 	int i = 0; */
/* 	built options[] = { */
/* 		{"env", built_env}, */
/* 		{"exit", built_exit}, */
/* 		{"unsetenv", built_unsetenv}, */
/* 		{"cd", built_cd}, */
/* 		{"help", built_help}, */
/* 		{"setenv", built_setenv}, */
/* 		{"alias", built_alias}, */
/* 		{NULL, NULL} */
/* 	}; */

/* 	while (options[i].key != NULL) */
/* 	{ */
/* 		if (strcmp(res->toks[0], options[i].key) == 0) */
/* 		{ */
/* 			options[i].func(res); */
/* 			return (1); */
/* 		} */
/* 		i++; */
/* 	} */
/* 	return (0); */
/* } */

/**
 * main - Main function to run the simple shell.
 *
 * @argc: Arguments counter.
 *
 * @argv: Arguments vector.
 *
 * Return: 0.
 */

int main(int argc __attribute__((unused)), char **argv)
{
	size_t n = 0;
	int bytes_read = 0, errors = 1, while_status = 1, flag = 0;
	char *command = NULL, *hold = NULL;
	response *req = NULL;

	while (while_status)
	{
		while_status = isatty(STDIN_FILENO);
		n = 0, flag = 0;
		if (while_status == 1)
			printf("$ ");
		bytes_read = getline(&command, &n, stdin);
		if (first_validations(command, bytes_read))
			continue;
		req = tokenize(command);

		/* match_built_in(); */

		if (route_works(req, &while_status))
			continue;
		if (fail_route(req, argv[0], &errors))
			continue;
		/* if (strchr(req->toks[0], '/')) */
		/* 	hold = find_char_rev(req->toks[0], '/'), req->toks[0] = hold, flag = 1; */
		req->hold = which(req->hold);
		validate_last_access(req, argv[0], &errors, &flag);
		free_all(&flag, req, hold, &while_status);
	}
	return (0);
}
