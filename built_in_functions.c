#include "main.h"

int built_env(response *res __attribute__ ((unused)))
{
	int i = 0;

	while (environ[i])
		printf("%s\n", environ[i]), i++;
	return (1);
}

int built_exit(response *res)
{
	free_tokens(res->toks);
	free(res->hold);
	free(res);
	exit(2);
}
