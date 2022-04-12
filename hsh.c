#include "main.h"

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
	int bytes_read = 0, errors = 1, while_st = 1, exit_status = 0;
	int validate = 0;
	char *command = NULL, *no_line = NULL;
	response *req = NULL;

	signal(SIGINT, c_handler);

	while (while_st)
	{
		while_st = isatty(STDIN_FILENO), n = 0;
		if (while_st == 1)
			write(1, "$ ", 2);
		bytes_read = getline(&command, &n, stdin);

		validate = first_validations(command, bytes_read, &while_st);
		if (validate == -1)
			break;
		else if (validate == 1)
			continue;

		no_line = strndup(command, bytes_read - 1), free(command);
		req = tokenize(no_line);

		if (match_built_in(req, &errors, argv[0], &exit_status))
		{
			free_all(req, &while_st);
			continue;
		}
		if (route_works(req, &while_st, &exit_status))
			continue;
		if (fail_route(req, argv[0], &errors, &exit_status))
			continue;
		req->hold = which(req->hold);
		validate_last_access(req, argv[0], &errors, &exit_status);
		free_all(req, &while_st);
	}
	return (0);
}
