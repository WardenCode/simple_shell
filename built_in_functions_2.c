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

int built_cd(response *res, int *errors, char *argv)
{
	int num_tokens = number_of_tokens(res->toks);
	char WD[256], *owd = getenv("OLDPWD");

	UNUSED(errors), UNUSED(argv);
	getcwd(WD, sizeof(WD));

	if (num_tokens <= 2)
		if (res->toks[1] == NULL || strcmp(res->toks[1], "~") == 0)
			chdir(getenv("HOME"));
		else if (strcmp(res->toks[1], "-") == 0)
			chdir(owd);
		else
			if (access(res->toks[1], F_OK) == 0)
				chdir(res->toks[1]);
			else
				printf("cd: no such file or directory: %s\n", res->toks[1]);
	else
		printf("Wrong number of arguments: Try use \"cd [directory]\"\n");

	setenv("OLDPWD", WD, 1);
	setenv("PWD", getcwd(WD, sizeof(WD)), 1);
	return (1);
}
