#include "main.h"

/**
 * only_the_command - Take the command (with route) and oly takes the command.
 *
 * @cmd: Route of the command.
 *
 * Return: Pointer to the name of the command.
 */

char *only_the_command(char *cmd)
{
	char *without_slash = NULL;
	int i = 0;

	for (i = strlen(cmd); cmd[i] != '/'; i--)
		;

	without_slash = strdup(&cmd[i]);
	free(cmd);
	return (without_slash);
}

/**
 * free_tokens - Free a double pointer that contains tokens of a command.
 *
 * @tokens: Double pointer with the information of the command.
 *
 * Return: Void
 */

void free_tokens(char **tokens)
{
	int i = 0;

	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

/**
 * do_the_command - Takes the tokens and execute shell commands.
 *
 * @res: Pointer to a structur (tokens and holder).
 *
 * @exit_status: Pointer to the exit status of the prev command.
 *
 * Return: Void
 */

void do_the_command(response *res, int *exit_status)
{
	pid_t child_pid = 0;
	int status_child = 0;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error"), _exit(1);
	}
	else if (child_pid == 0)
	{
		execve(clean_spaces(res->hold), res->toks, environ);
		free_tokens(res->toks);
		free(res->hold);
		free(res);
		_exit(1);
	}
	else
	{
		waitpid(-1, &status_child, 0);

		if (WEXITSTATUS(status_child))
			*exit_status = WEXITSTATUS(status_child);
	}
}

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
