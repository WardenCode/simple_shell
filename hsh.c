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
	int bytes_read = 0, errors = 1, while_status = 1, exit_status = 0;
	char *command = NULL;
	response *req = NULL;

	signal(SIGINT, c_handler);

	while (while_status)
	{
		while_status = isatty(STDIN_FILENO), n = 0;

		if (while_status == 1)
			write(1, "$ ", 2);

		bytes_read = getline(&command, &n, stdin);

		if (first_validations(command, bytes_read) >= 1)
			break;

		req = tokenize(command);

		if (match_built_in(req, &errors, argv[0], &exit_status))
		{
			free_all(req, &while_status);
			continue;
		}

		if (route_works(req, &while_status, &exit_status))
			continue;

		if (fail_route(req, argv[0], &errors))
			continue;

		req->hold = which(req->hold);

		validate_last_access(req, argv[0], &errors, &exit_status);

		free_all(req, &while_status);
	}
	return (0);
}
