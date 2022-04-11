#include "main.h"

/**
 * fail_route - Validates if a route fails.
 *
 * @req: Pointer to a structure.
 *
 * @argv: Arguments vector.
 *
 * @err: Pointer to the counter of errors.
 *
 * Return: 1 if the route fails, 0 otherwise.
 */

int fail_route(response *req, char *argv, int *err)
{
	if (access(req->toks[0], F_OK) != 0 && strchr(req->toks[0], '/'))
	{
		printf("%s: %d: %s :not found\n", argv, *err, clean_spaces(req->toks[0]));
		free_tokens(req->toks);
		free(req->hold);
		free(req);
		*err += 1;
		return (1);
	}
	return (0);
}

/**
 * clean_spaces - Find the spaces and clean it.
 *
 * @command: Command to search.
 *
 * Return: The path if success, NULL if failure.
 */

char *clean_spaces(char *command)
{
	int i = 0;

	while (command[i] != '\0')
	{
		if (command[i] != ' ' && command[i] != '\t')
			return (&command[i]);
		i++;
	}
	return (NULL);
}

/**
 * which - Search the path of a command
 *
 * @command: Command to search.
 *
 * Return: The path if success, NULL if failure.
 */

char *which(char *command)
{
	char *path = NULL, *route = "\0", *full = NULL, *holder = NULL;
	char *command_holder = NULL;

	if (!command)
		return (NULL);
	path = str_concat(getenv("PATH"), ":");
	holder = path;

	command_holder = clean_spaces(command);

	while (route != NULL)
	{
		route = strchr(holder, ':');
		if (!route)
			break;

		route[0] = '\0';

		full = validate_slash(command_holder, holder);

		if (access(full, 0) == 0)
		{
			free(path);
			free(command);
			return (full);
		}
		else
		{
			holder = route + 1;
			free(full);
			continue;
		}
	}
	free(path);
	return (command);
}