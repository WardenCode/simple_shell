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
		free_tokens(obj->toks);
		free(obj);
		*while_status = 1;
		return (1);
	}
	return (0);
}

/**
 * free_all - Function that free all the malloc of the program.
 *
 * @flag: Pointer to a flag.
 *
 * @obj: Pointer to a structure (tokens and holder)
 *
 * @hold: Pointer to a holder.
 *
 * @while_status: Status of the infinite while..
 *
 * Return: Void.
 */

void free_all(int *flag, response *obj, char *hold, int *while_status)
{
	(*flag == 0 || *flag == 2) ? free(obj->hold) : free(hold);

	free_tokens(obj->toks);
	free(obj);
	*while_status = 1;
}

/**
 * fail_route - Validates if a route fails.
 *
 * @req: Pointer to a .
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
		printf("%s: %d: %s :not found\n", argv, *err, req->toks[0]);
		free_tokens(req->toks), free(req), *err += 1;
		return (1);
	}
	return (0);
}

/* /\** */
/*  * clean_spaces - Find the spaces and clean it. */
/*  * */
/*  * @command: Command to search. */
/*  * */
/*  * Return: The path if success, NULL if failure. */
/*  *\/ */

/* char *clean_spaces(char *command) */
/* { */
/* 	int i = 0; */

/* 	while (command[i] != '\0') */
/* 	{ */
/* 		if (command[i] != ' ') */
/* 			return (&command[i]); */
/* 		i++; */
/* 	} */
/* 	return (NULL); */
/* } */
