#include "main.h"

/**
 * find_char - Search a char inside of a str beginning with the end
 *
 * @str: String to search a char.
 *
 * @character: char to search in the str.
 *
 * Return: A pointer to the string after the char, if not find that char return
 * the str completed.
 */

char *find_char_rev(char *str, char character) /*Here*/
{
	char *result = NULL;
	ssize_t i = 0, j = 0, k = 0, counter = 0;

	for (i = strlen(str); i >= 0; i--)
	{
		if (str[i] == character)
			break;
		counter++;
	}

	/* counter++; */

	result = malloc((counter) * sizeof(char));
	if (!result)
		return (NULL);

	/* result = strdup(&str[strlen(str) - counter + 1]); */
	for (j = 0, k = strlen(str) - counter + 1; j < counter; j++)
		result[j] = str[k + j];

	/* free(str); */
	return (result);
}

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

void free_tokens(char **tokens)/*Here*/
{
	free(tokens[0]);
	free(tokens);
}

void do_the_command(char **tokens)
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
		execve(tokens[0], tokens, environ);
		free_tokens(tokens);
		_exit(1);
	}
	else
	{
		wait(&status_child);
	}
}
