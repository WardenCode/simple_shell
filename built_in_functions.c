#include "main.h"

/**
 * match_built_in - Find if the built in to use.
 *
 * @res: Pointer to the structure (tokens, holder).
 *
 * @errors: Pointer to the counter of errors.
 *
 * @argv: Name of the executable.
 *
 * Return: Return 1 if use a function, 0 otherwise.
 */

int match_built_in(response *res, int *errors, char *argv)
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
		if (strcmp(res->toks[0], options[i].key) == 0)
		{
			options[i].func(res, errors, argv);
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * built_env - Command of the simple shell to show the environment.
 *
 * @res: Pointer to the structure (tokens, holder).
 *
 * @errors: Pointer to the counter of errors.
 *
 * @argv: Name of the executable.
 *
 * Return: Return 1 if use a function, 0 otherwise.
 */

int built_env(response *res, int *errors, char *argv)
{
	int i = 0, number_tokens = 0;

	UNUSED(errors), UNUSED(argv);

	number_tokens = number_of_tokens(res->toks);

	if (number_tokens >= 2)
	{
		printf("env: '%s': No such file or directory\n", res->toks[1]);
		return (1);
	}

	while (environ[i])
		printf("%s\n", environ[i]), i++;
	return (1);
}

/**
 * built_exit - Command of the simple shell to exit with status.
 *
 * @res: Pointer to the structure (tokens, holder).
 *
 * @errors: Pointer to the counter of errors.
 *
 * @argv: Name of the executable.
 *
 * Return: Return 1 if use a function, 0 otherwise.
 */

int built_exit(response *res, int *errors, char *argv)
{
	int number_tokens = 0, new_number = 0;

	number_tokens = number_of_tokens(res->toks);

	if (number_tokens == 1)
	{
		free_tokens(res->toks);
		free(res->hold);
		free(res);
		exit(2);
	}

	if (is_number(res->toks[1]))
	{
		new_number = atoi(res->toks[1]);
	}
	else
	{
		printf("%s: %d: exit: Illegal number: %s\n", argv, *errors, res->toks[1]);
		*errors += 1;
		return (1);
	}

	free_tokens(res->toks);
	free(res->hold);
	free(res);
	exit(new_number);
}

/**
 * built_setenv - Command to set or overwrite a env variable.
 *
 * @res: Pointer to the structure (tokens, holder).
 *
 * @errors: Pointer to the counter of errors.
 *
 * @argv: Name of the executable.
 *
 * Return: Return 1 if use a function, 0 otherwise.
 */

int built_setenv(response *res, int *errors, char *argv)
{
	int num_tokens = number_of_tokens(res->toks);

	UNUSED(errors), UNUSED(argv);

	if (num_tokens == 3)
		setenv(res->toks[1], res->toks[2], 1);
	else if (num_tokens < 3)
		fprintf(stderr, "To few arguments: Try use \"setenv [KEY] [VALUE]\"\n");
	else
		fprintf(stderr, "To many arguments: Try use \"setenv [KEY] [VALUE]\"\n");

	return (1);
}

/**
 * built_unsetenv - Command of the simple shell eliminate a env var.
 *
 * @res: Pointer to the structure (tokens, holder).
 *
 * @errors: Pointer to the counter of errors.
 *
 * @argv: Name of the executable.
 *
 * Return: Return 1 if use a function, 0 otherwise.
 */

int built_unsetenv(response *res, int *errors, char *argv)
{
	int num_tokens = number_of_tokens(res->toks);

	UNUSED(errors), UNUSED(argv);

	if (num_tokens == 2)
		unsetenv(res->toks[1]);
	else
		fprintf(stderr, "Wrong number of arguments: Try use \"unsetenv [KEY]\"\n");

	return (1);
}
