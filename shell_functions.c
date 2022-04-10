#include "main.h"

/**
 * find_char_rev - Search a char inside of a str beginning with the end.
 *
 * @str: String to search a char.
 *
 * @character: char to search in the str.
 *
 * Return: A pointer to the string after the char, if not find that char return
 * the str completed.
 */

char *find_char_rev(char *str, char character)
{
	char *result = NULL;
	ssize_t i = 0, j = 0, k = 0, counter = 0;

	for (i = strlen(str); i >= 0; i--)
	{
		if (str[i] == character)
			break;
		counter++;
	}

	result = malloc((counter) * sizeof(char));
	if (!result)
		return (NULL);

	for (j = 0, k = strlen(str) - counter + 1; j < counter; j++)
		result[j] = str[k + j];

	free(str);
	return (result);
}

/**
 * no_new_line - Copy a pointer of the function getline and delete the '\n'.
 *
 * @command: Source command.
 *
 * @new_command: Pointer to the new command (without '\n').
 *
 * Return: Pointer to the command without new line.
 */

char *no_new_line(char *command, char *new_command)
{
	int i = 0, size = 0;

	size = strlen(command);
	new_command = malloc(sizeof(char) * (size));
	if (!new_command)
	{
		free(command);
		return (NULL);
	}
	for (i = 0; i <= size - 1; i++)
		new_command[i] = command[i];
	new_command[i - 1] = '\0';
	return (new_command);
}

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
 * Return: Void
 */

void do_the_command(response *res)
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
		wait(&status_child);
	}
}
