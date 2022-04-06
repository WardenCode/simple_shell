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

	i++;

	result = malloc((counter) * sizeof(char));

	for (j = 0, k = strlen(str) - counter + 1; j < counter; j++)
		result[j] = str[k + j];

	/* result[j] = '\0'; */

	free(str);
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
		exit(0);
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

void do_the_command(char *new_command)
{
	pid_t child_pid = 0;
	int status_child = 0;
	char *instruction[] = {new_command, NULL};

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error"), _exit(1);
	}
	else if (child_pid == 0)
	{
		execve(instruction[0], instruction, environ);
		_exit(1);
	}
	else
		wait(&status_child);
}
