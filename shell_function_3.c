#include "main.h"

/**
 * route_works - Validate if a route works or not.
 *
 * @obj: Pointer to an structure (tokens, holder).
 *
 * @while_status: Status of the infinite while.
 *
 * Return: 0 if the route fails, 1 otherwise.
 */

int route_works(response *obj, int *while_status)
{
	if (access(obj->toks[0], F_OK) == 0)
	{
		do_the_command(obj);
		free_all(obj, while_status);
		*while_status = 1;
		return (1);
	}
	return (0);
}

/**
 * free_all - Function that free all the malloc of the program.
 *
 * @obj: Pointer to a structure (tokens and holder)
 *
 * @while_status: Status of the infinite while..
 *
 * Return: Void.
 */

void free_all(response *obj, int *while_status)
{
	free_tokens(obj->toks);
	free(obj->hold);
	free(obj);
	*while_status = 1;
}

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
