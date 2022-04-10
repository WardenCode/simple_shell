#include "main.h"

/**
 * match_built_in - Find if the built in to use.
 *
 * @res: Pointer to the structure (tokens, holder).
 *
 * Return: Return 1 if use a function, 0 otherwise.
 */

int match_built_in(response *res, int *errors, char *argv)
{
	int i = 0;
	built options[] = {
		{"env", built_env},
		{"exit", built_exit},
		/* {"unsetenv", built_unsetenv}, */
		/* {"cd", built_cd}, */
		/* {"help", built_help}, */
		/* {"setenv", built_setenv}, */
		/* {"alias", built_alias}, */
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

void c_handler(int x)
{
	UNUSED(x);
	write(1,"\n$ ", 3);
}

int validate_file(int argc, char *file)
{
	int exists = 0;

	if (file == NULL)
		return (exists);

	if (argc == 2)
		access(file, F_OK) == 0 ? exists = 1 : printf("error to see the file");

	return (exists);
}

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
	int bytes_read = 0, errors = 1, while_status = 1;
	char *command = NULL;
	response *req = NULL;

	signal(SIGINT, c_handler);

	while (while_status)
	{
		while_status = isatty(STDIN_FILENO), n = 0;
		if (while_status == 1)
			write(1, "$ ", 2);

		bytes_read = getline(&command, &n, stdin);

		if (first_validations(command, bytes_read))
			continue;
		req = tokenize(command);

		if (match_built_in(req, &errors, argv[0]))
		{
			free_all(req, &while_status);
			continue;
		}

		if (route_works(req, &while_status))
			continue;
		if (fail_route(req, argv[0], &errors))
			continue;

		req->hold = which(req->hold);
		validate_last_access(req, argv[0], &errors);
		free_all(req, &while_status);
	}
	return (0);
}
