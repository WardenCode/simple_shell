#include "main.h"

/**
 * first_validation - 
 *
 * @argc: Arguments counter.
 *
 * @argv: Arguments vector.
 *
 * Return: 0.
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
 * main - Main function to run the simple shell.
 *
 * @argc: Arguments counter.
 *
 * @argv: Arguments vector.
 *
 * Return: 0.
 */

void validate_last_access(char **tokens, char *file, int *errors, int *flag)
{
	if (access(tokens[0], F_OK) != 0)
	{
		printf("%s: %d: %s :not found\n", file, *errors, tokens[0]);
		errors++;
		*flag = ((flag == 0) ? -1 : 2);
	}
	else
	{
		do_the_command(tokens);
	}
}

/**
 * main - Main function to run the simple shell.
 *
 * @argc: Arguments counter.
 *
 * @argv: Arguments vector.
 *
 * Return: 0.
 */

int main(int argc __attribute__((unused)), char **argv)
{
	size_t n = 0;
	int bytes_read = 0, errors = 1, while_status = 1, flag = 0;
	char *command = NULL, *hold = NULL;
	response *req = NULL;

	while (while_status)
	{
		while_status = isatty(STDIN_FILENO);
		n = 0, flag = 0;

		if (while_status == 1)
			printf("$ ");

		bytes_read = getline(&command, &n, stdin);

		if (first_validations(command, bytes_read))
			continue;

		req = tokenize(command);

		if (access(req->toks[0], F_OK) == 0)
		{
			do_the_command(req->toks);
			free_tokens(req->toks);
			free(req);
			while_status = 1;
			continue;
		}

		if (access(req->toks[0], F_OK) != 0 && strchr(req->toks[0], '/'))
		{
			printf("%s: %d: %s :not found\n", argv[0], errors, req->toks[0]);
			free_tokens(req->toks), free(req), errors++;
			continue;
		}

		if (strchr(req->toks[0], '/'))
		{
			hold = find_char_rev(req->toks[0], '/');
			req->toks[0] = hold;
			flag = 1;
		}

		req->toks[0] = which(req->toks[0]);

		/* if (access(req->toks[0], F_OK) != 0) */
		/* { */
		/* 	printf("%s: %d: %s :not found\n", argv[0], errors, req->toks[0]), errors++; */
		/* 	flag = ((flag == 0) ? -1 : 2); */
		/* } */
		/* else */
		/* { */
		/* 	do_the_command(req->toks); */
		/* } */

		validate_last_access(req->toks, argv[0], &errors, &flag);

		(flag == 0 || flag == 2) ? free(req->hold) : free(hold);
		free_tokens(req->toks), free(req), while_status = 1;
	}
	return (0);
}
