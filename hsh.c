#include "main.h"

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

	without_slash = &cmd[i];
	return (without_slash);
}

void do_the_command(char *old_command, char *new_command)
{
	pid_t child_pid = 0;
	int status_child = 0;
	char *instruction[] = {new_command, NULL};

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error");
		_exit(1);
	}
	else if (child_pid == 0)
	{
		if (access(new_command, F_OK) == 0)
			execve(instruction[0], instruction, NULL);
		free(old_command), free(new_command);
		_exit(1);
		/* kill(getpid(), SIGKILL); */
	}
	else
	{
		wait(&status_child);
	}
}

int main(void)
{
	size_t n = 0;
	int bytes_read = 0;
	char *command = NULL;
	char *no_line = NULL;

	while (1)
	{
		n = 0;
		printf("$ ");
		bytes_read = getline(&command, &n, stdin);
		if (bytes_read == -1 || strcmp(command, "EOF\n") == 0)
		{
			free(command);
			printf("\n");
			_exit(1);
		}
		else
		{
			if (command[0] == '\n' || strlen(command) == 2)
			{
				free(command);
				continue;
			}
			no_line = no_new_line(command, no_line);
			if (!find_char(no_line, '/'))
				no_line = only_the_command(no_line);
			no_line = which(no_line);
			do_the_command(command, no_line);
			free(no_line);
		}
	}
	return (0);
}
