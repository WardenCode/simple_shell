#include "main.h"

/* int find_total_spaces(char *command) */
/* { */
/* 	int i = 0, counter = 0; */

/* 	while (command[i]) */
/* 	{ */
/* 		if (command[i] == ' ') */
/* 			counter++; */
/* 		i++; */
/* 	} */

/* 	return (counter); */
/* } */

/* char **get_tokens(char *command) */
/* { */
/* 	char **tokens = NULL; */
/* 	char *token = NULL; */
/* 	int spaces = find_total_spaces(command); */

/* 	tokens = malloc(sizeof(char *) * (spaces + 1)); */

/* 	token = strtok(command, " "); */
/* 	while (command != NULL) */
/* 	{ */
/* 		tokens = &token; */
/* 		token = strtok(NULL, " "); */
/* 	} */

/* 	return (tokens); */
/* } */

/* void free_tokens(char **tokens) */
/* { */

/* } */

int main(int arg __attribute__((unused)), char **argv)
{
	size_t n = 0;
	int bytes_read = 0;
	char *command = NULL;
	char *no_line = NULL;
	/* char **tokend = NULL; */

	while (1)
	{
		n = 0;
		printf("$ ");
		bytes_read = getline(&command, &n, stdin);
		if (bytes_read == -1 || strcmp(command, "EOF\n") == 0)
		{
			free(command), printf("\n"), _exit(1);
		}
		else
		{
			if (command[0] == '\n')
			{
				free(command);
				continue;
			}
			no_line = no_new_line(command, no_line);
			command[strlen(command) - 1] = '\0';
			if (access(no_line, F_OK) != 0 && strchr(no_line, '/'))
			{
				printf ("%s: 1: %s :not found\n", argv[0], command);
				free(no_line), free(command);
				continue;
			}
			no_line = find_char_rev(no_line, '/');
			if (!no_line)
				no_line = only_the_command(no_line);
			no_line = which(no_line);
			if (access(no_line, F_OK) == 0)
				do_the_command(no_line), free(no_line);
			else
				printf ("%s: 1: %s :not found\n", argv[0], command);
			free(command);
		}
	}
	return (0);
}
