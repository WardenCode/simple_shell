#include "main.h"

/**
 * match_built_in - Find if the built in to use.
 *
 * @r: Pointer to the structure (tokens, holder).
 *
 * @err: Pointer to the counter of errors.
 *
 * @av: Name of the executable.
 *
 * @exit_status: Pointer to the exit status of the prev command.
 *
 * Return: Return 1 if use a function, 0 otherwise.
 */

int match_built_in(response *r, int *err, char *av, int *exit_status)
{
	int i = 0;
	built options[] = {
		{"env", built_env},
		{"exit", built_exit},
		{"unsetenv", built_unsetenv},
		{"setenv", built_setenv},
		{"cd", built_cd},
		/* {"help", built_help}, */
		/* {"alias", built_alias} */
		{NULL, NULL}
	};

	while (options[i].key != NULL)
	{
		if (strcmp(r->toks[0], options[i].key) == 0)
		{
			options[i].func(r, err, av, exit_status);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * built_env - Command of the simple shell to show the environment.
 *
 * @r: Pointer to the structure (tokens, holder).
 *
 * @err: Pointer to the counter of errors.
 *
 * @av: Name of the executable.
 *
 * @exit_status: Pointer to the exit status of the prev command.
 *
 * Return: Return 1 if use a function, 0 otherwise.
 */

int built_env(response *r, int *err, char *av, int *exit_status)
{
	int i = 0, number_tokens = 0;

	UNUSED(err), UNUSED(av), UNUSED(exit_status);

	number_tokens = number_of_tokens(r->toks);

	if (number_tokens >= 2)
	{
		fprintf(stderr, "env: '%s': No such file or directory\n", r->toks[1]);
		return (1);
	}

	while (environ[i])
		printf("%s\n", environ[i]), i++;
	return (1);
}

/**
 * built_exit - Command of the simple shell to exit with status.
 *
 * @r: Pointer to the structure (tokens, holder).
 *
 * @err: Pointer to the counter of errors.
 *
 * @av: Name of the executable.
 *
 * @exit_status: Pointer to the exit status of the prev command.
 *
 * Return: Return 1 if use a function, 0 otherwise.
 */

int built_exit(response *r, int *err, char *av, int *exit_status)
{
	int number_tokens = 0, new_number = 0;

	number_tokens = number_of_tokens(r->toks);

	if (number_tokens == 1)
	{
		free_tokens(r->toks);
		free(r->hold);
		free(r);
		exit(*exit_status);
	}

	if (is_number(r->toks[1]) && atoi(r->toks[1]) >= 0)
	{
		new_number = atoi(r->toks[1]);
	}
	else
	{
		fprintf(stderr, "%s: %d: exit: Illegal number: %s\n", av, *err, r->toks[1]);
		*err += 1;
		*exit_status = 2;
		free_tokens(r->toks);
		free(r->hold);
		free(r);
		exit(2);
		return (1);
	}

	free_tokens(r->toks);
	free(r->hold);
	free(r);
	exit(new_number);
}

/**
 * built_setenv - Command to set or overwrite a env variable.
 *
 * @r: Pointer to the structure (tokens, holder).
 *
 * @err: Pointer to the counter of errors.
 *
 * @av: Name of the executable.
 *
 * @exit_status: Pointer to the exit status of the prev command.
 *
 * Return: Return 1 if use a function, 0 otherwise.
 */

int built_setenv(response *r, int *err, char *av, int *exit_status)
{
	int num_tokens = number_of_tokens(r->toks);

	UNUSED(err), UNUSED(av), UNUSED(exit_status);

	if (num_tokens == 3)
		setenv(r->toks[1], r->toks[2], 1);
	else if (num_tokens < 3)
		fprintf(stderr, "To few arguments: Try use \"setenv [KEY] [VALUE]\"\n");
	else
		fprintf(stderr, "To many arguments: Try use \"setenv [KEY] [VALUE]\"\n");

	return (1);
}

/**
 * built_unsetenv - Command of the simple shell eliminate a env var.
 *
 * @r: Pointer to the structure (tokens, holder).
 *
 * @err: Pointer to the counter of errors.
 *
 * @av: Name of the executable.
 *
 * @exit_status: Pointer to the exit status of the prev command.
 *
 * Return: Return 1 if use a function, 0 otherwise.
 */

int built_unsetenv(response *r, int *err, char *av, int *exit_status)
{
	int num_tokens = number_of_tokens(r->toks);

	UNUSED(err), UNUSED(av), UNUSED(exit_status);

	if (num_tokens == 2)
		unsetenv(r->toks[1]);
	else
		fprintf(stderr, "Wrong number of arguments: Try use \"unsetenv [KEY]\"\n");

	return (1);
}
