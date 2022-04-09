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

	while (command[i] == ' ' || command[i] == '\n' || command[i] == '\t')
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
	int i = 0, counter = 0;

	while (command[i] != '\0')
	{
		if (command[i] == ' ' || command[i] == '\t')
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

struct response *tokenize(char *input)
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
		tokens[i] = token;
		token = strtok(NULL, " \n\t");
		i++;
	}
	tokens[i] = NULL;
	res->toks = tokens;
	res->hold = holder;
	return (res);
}
