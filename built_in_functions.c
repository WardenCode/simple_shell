#include "main.h"

int built_env(response *res, int *errors, char *argv)
{
	int i = 0, number_tokens = 0;

	UNUSED(errors), UNUSED(argv);

	number_tokens = number_of_tokens(res->toks);

	if (number_tokens >= 2)
	{
		printf("env: '%s': No such file or directory\n", res->toks[1]);
		return (1);
	}

	while (environ[i])
		printf("%s\n", environ[i]), i++;
	return (1);
}

int built_exit(response *res, int *errors, char *argv)
{
	int number_tokens = 0, new_number = 0;

	number_tokens = number_of_tokens(res->toks);

	if (number_tokens == 1)
	{
		free_tokens(res->toks);
		free(res->hold);
		free(res);
		exit(2);
	}

	if (is_number(res->toks[1]))
	{
		new_number = atoi(res->toks[1]);
	}
	else
	{
		printf("%s: %d: exit: Illegal number: %s\n", argv, *errors, res->toks[1]);
		*errors += 1;
		return (1);
	}

	free_tokens(res->toks);
	free(res->hold);
	free(res);
	exit(new_number);
}
