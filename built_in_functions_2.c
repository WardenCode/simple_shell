#include "main.h"

/**
 * built_cd - Change directory.
 *
 * @res: Pointer to the structure (tokens, holder).
 *
 * @errors: Pointer to the counter of errors.
 *
 * @argv: Name of the executable.
 *
 * Return: Return 1.
 */

int built_cd(response *r, int *err, char *av)
{
	int num_tokens = number_of_tokens(r->toks);
	char WD[256], *owd = getenv("OLDPWD");

	UNUSED(err), UNUSED(av);
	getcwd(WD, sizeof(WD));

	if (num_tokens <= 2)
		if (r->toks[1] == NULL || strcmp(r->toks[1], "~") == 0)
			chdir(getenv("HOME"));
		else if (strcmp(r->toks[1], "-") == 0)
			chdir(owd);
		else
			if (access(r->toks[1], F_OK) == 0)
				chdir(r->toks[1]);
			else
				printf("cd: no such file or directory: %s\n", r->toks[1]);
	else
		printf("Wrong number of arguments: Try use \"cd [directory]\"\n");

	setenv("OLDPWD", WD, 1);
	setenv("PWD", getcwd(WD, sizeof(WD)), 1);
	return (1);
}
