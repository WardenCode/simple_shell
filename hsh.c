#include "main.h"

int total_malloc(char *command)
{
	int i = 0, counter = 0;

	while (command[i] != '\0')
	{
		if (command[i] == ' ')
			counter++;
		i++;
	}

	return (counter /* + 1 */+ 2);
}

/* char **tokenize(char *input) */
/* { */
/* 	char **tokens = NULL, *token = NULL, *holder = NULL; */
/* 	int spaces = total_malloc(input), i = 0; */

/* 	/\* printf("spaces: %d\n", spaces); *\/ */

/* 	tokens = malloc(sizeof(char *) * (spaces)); */
/* 	if (!tokens) */
/* 		return (NULL); */
/* 	holder = strdup(input); */
/* 	token = strdup(strtok(holder, " \n\t")); */
/* 	free(input); */
/* 	while (token != NULL) */
/* 	{ */
/* 		tokens[i] = token; */
/* 		token = strtok(NULL, " \n\t"); */
/* 		i++; */
/* 	} */
/* 	/\*Maybe necesary*\/ */
/* 	tokens[i] = NULL; */

/* 	/\* free(holder); *\/ */
/* 	return (tokens); */
/* } */

struct response *tokenize(char *input)
{
	char **tokens = NULL, *token = NULL, *holder = NULL;
	int spaces = total_malloc(input), i = 0;
	response *res = NULL;

	res = malloc(sizeof(response));

	/* printf("spaces: %d\n", spaces); */

	tokens = malloc(sizeof(char *) * (spaces));
	if (!tokens)
		return (NULL);
	holder = strdup(input);
	token = strtok(holder, " \n\t");
	free(input);
	while (token != NULL)
	{
		tokens[i] = token;
		token = /* strdup( */strtok(NULL, " \n\t")/* ) */;
		i++;
	}
	/*Maybe necesary*/
	tokens[i] = NULL;
	res->toks = tokens;
	res->hold = holder;
	/* free(holder); */
	return (res);
}

int main(int arg __attribute__((unused)), char **argv)
{
	size_t n = 0;
	int bytes_read = 0, errors = 1;
	char *command = NULL/* , **tokens = NULL */;
	response *req = NULL;
	int while_status = 1;

	while (while_status)
	{
		while_status = isatty(STDIN_FILENO);
		n = 0;

		if (while_status == 1)
			printf("$ ");

		bytes_read = getline(&command, &n, stdin);

		/* command[bytes_read - 1] = '\0'; */

		if (bytes_read == -1)
			free(command), printf("\n"),_exit(1);

		if (command[0] == '\n')
		{
			free(command);
			continue;
		}

		/* tokens = tokenize(command); */
		req = tokenize(command);
		/* free(command); */

		/* if (access(tokens[0], F_OK) != 0 && strchr(tokens[0], '/')) */
		if (access(req->toks[0], F_OK) != 0 && strchr(req->toks[0], '/'))
		{
			/* printf ("%s: %d: %s :not found\n", argv[0], errors, tokens[0]); */
			printf("%s: %d: %s :not found\n", argv[0], errors, req->toks[0]);
			/* free_tokens(tokens); */
			free_tokens(req->toks);
			free(req->hold);
			errors++;
			continue;
		}

		/* if (strchr(tokens[0], '/')) */
		/* { */
		/* 	tokens[0] = find_char_rev(tokens[0], '/'); */
		/* } */

		if (strchr(req->toks[0], '/'))
		{
			req->toks[0] = find_char_rev(req->toks[0], '/');
		}
		/* if (!tokens) */
		/* 	tokens[0] = only_the_command(tokens[0]); */

		/* tokens[0] = which(tokens[0]); */
		/* /\* free(command); *\/ */
		/* if (access(tokens[0], F_OK) != 0) */
		/* 	printf("%s: %d: %s :not found\n", argv[0], errors, tokens[0]), errors++; */
		/* else */
		/* 	do_the_command(tokens); */
		/* free_tokens(tokens); */

		req->toks[0] = which(req->toks[0]);
		/* free(command); */
		if (access(req->toks[0], F_OK) != 0)
			printf("%s: %d: %s :not found\n", argv[0], errors, req->toks[0]), errors++;
		else
			do_the_command(req->toks);
		free_tokens(req->toks);
		/* free(req->toks); */
		free(req->hold);
		free(req);
		/* if (command) */
		/* 	free(command); */
	}
	return (0);
}
