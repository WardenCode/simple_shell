#include "main.h"

/**
 * tokenize - Takes the input and tokenize command and arguments.
 *
 * @input: Input of the getline (with a command and parameters).
 *
 * Return: A structure with the tokens and a holder to free later.
 */

response *tokenize(char *input)
{
	char **tokens = NULL, *token = NULL, *holder = NULL;
	int spaces = total_malloc(input), i = 0;
	response *res = NULL;

	res = malloc(sizeof(response));
	if (!res)
		return (NULL);

	tokens = malloc(sizeof(char *) * (spaces));
	if (!tokens)
		return (NULL);

	holder = strdup(input);
	token = strtok(holder, " \n\t");
	free(input);
	while (token != NULL)
	{
		tokens[i] = strdup(token);
		token = strtok(NULL, " \n\t");
		i++;
	}
	tokens[i] = NULL;
	res->toks = tokens;
	res->hold = holder;
	return (res);
}

/**
 * first_validations - Validations after the getline (all spaces or errors).
 *
 * @command: Command (input) of the getline.
 *
 * @bytes_read: Lenght of the command.
 *
 * Return: 0 if all good, 1 otherwise.
 */

int first_validations(char *command, int bytes_read)
{
	if (bytes_read == -1)
	{
		free(command);
		return (2);
	}

	if (all_spaces(command, bytes_read))
	{
		free(command);
		return (1);
	}
	return (0);
}

/**
 * validate_last_access - Validate if the token[0] is a correct route or not
 *
 * @res: Pointer to an structure (tokens and holder).
 *
 * @file: Pointer to the name of the executable.
 *
 * @errors: Pointer to the counter of errors ocurred on the shell.
 *
 * Return: 0.
 */

void validate_last_access(response *r, char *file, int *err)
{
	if (access(r->hold, F_OK) != 0)
	{
		fprintf(stderr, "%s: %d: %s :not found\n", file, *err, clean_spaces(r->hold));
		*err += 1;
	}
	else
	{
		do_the_command(r);
	}
}

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
