#include "main.h"

int total_malloc(char *command)
{
	int i = 0, counter = 0;

	while (command[i])
	{
		if (command[i] == ' ')
			counter++;
		i++;
	}

	return (counter + 1);
}

char **tokenize(char *input)
{
	char **tokens = NULL, *token = NULL/* , *last_token = NULL */;
	int spaces = total_malloc(input), i = 0;

	tokens = malloc(sizeof(char *) * (spaces));

	token = strtok(input, " \n\t");
	while (token != NULL)
	{
		/* if (i == spaces - 2) */
		/* { */
		/* 	last_token = no_new_line(token, last_token); */
		/* 	tokens[i] = strdup(last_token); */
		/* 	free(last_token); */
		/* } */
		/* else */
		/* { */
		/* 	tokens[i] = token; */
		/* } */
		tokens[i] = token;
		/* printf("token: %s\n", tokens[i]); */
		token = strtok(NULL, " \n\t");
		i++;
	}
	/* tokens[i] = NULL; */
	/* free(input); */
	return (tokens);
}

int main(int arg __attribute__((unused)), char **argv)
{
	size_t n = 0;
	int bytes_read = 0, errors = 1;
	char *command = NULL, *holder = NULL, **tokens = NULL;
	int while_status = 1;

	while (while_status)
	{
		while_status = isatty(STDIN_FILENO);
		n = 0;

		if (while_status == 1)
			printf("$ ");

		bytes_read = getline(&command, &n, stdin);

		if (bytes_read == -1)
			free(command), printf("\n"),_exit(1);

		if (command[0] == '\n')
		{
			free(command);
			continue;
		}

		tokens = tokenize(command); // /bin///dasdasd/asd/ls
		free(command);

		if (access(tokens[0], F_OK) != 0 && strchr(tokens[0], '/'))
		{
			printf ("%s: %d: %s :not found\n", argv[0], errors, tokens[0]);
			free_tokens(tokens);
			/* free(command); */
			errors++;
			continue;
		}

		if (strchr(tokens[0], '/'))
			tokens[0] = find_char_rev(tokens[0], '/');

		if (!tokens)
			tokens[0] = only_the_command(tokens[0]);

		holder = which(tokens[0]);
		tokens[0] = holder;
		free(holder);

		if (access(tokens[0], F_OK) != 0)
			printf("%s: %d: %s :not found\n", argv[0], errors, tokens[0]), errors++;
		else
			do_the_command(tokens);
		free_tokens(tokens);
		/* if (command != NULL) */
		/* 	free(command); */
		/* free(command); */
	}
	return (0);
}
