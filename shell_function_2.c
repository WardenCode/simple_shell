#include "main.h"

/**
 * all_spaces - Validate if the command of input is composed by spaces.
 *
 * @command: Command to go through
 *
 * @size: The size of the command (input)
 *
 * Return: Flag with the value of the search, 1 if only found spaces, \n and \t
 * 0 otherwise.
 */

int all_spaces(char *command, ssize_t size)
{
	ssize_t i = 0, flag = 1;

	while (command[i] == ' ' || command[i] == '\n' || command[i] == '\t'
	       || command[i] == '/')
		i++;

	if (i != size)
		flag = 0;

	return (flag);
}

/**
 * total_malloc - Calculate the spaces and tabs to calculate
 * the malloc's quantity to use.
 *
 * @command: Command to analyze.
 *
 * Return: The malloc's quantity to use.
 */

int total_malloc(char *command)
{
	int i = 0, counter = 0, flag = 0;

	while (command[i] != '\0')
	{
		if (command[i] != ' ' && command[i] != '\t')
			flag = 1;

		if ((command[i] == ' ' || command[i] == '\t') && flag == 1)
			counter++;
		i++;
	}
	return (counter + 2);
}

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
		free(command), printf("\n"), _exit(1);

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

void validate_last_access(response *res, char *file, int *errors)
{
	if (access(res->hold, F_OK) != 0)
	{
		printf("%s: %d: %s :not found\n", file, *errors, clean_spaces(res->hold));
		*errors += 1;
	}
	else
	{
		do_the_command(res);
	}
}
