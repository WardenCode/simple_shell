#include "main.h"

/**
 * c_handler - Handle the Ctrl + C on the simple shell.
 *
 * @x: Unused int.
 *
 * Return: Void.
 */

void c_handler(int x)
{
	UNUSED(x);
	write(1, "\n$ ", 3);
}

/**
 * number_of_tokens - Calculate the num of tokens.
 *
 * @tokens: Double pointer to tokens.
 *
 * Return: Return the quantity of the tokens.
 */

int number_of_tokens(char **tokens)
{
	int number = 0;

	while (tokens[number])
		number++;

	return (number);
}

/**
 * find_points - Find double points in a string.
 *
 * @key: The string to search inside.
 *
 * Return: A new string, all the caracters behind that double points.
 */

char *find_points(char *key)
{
	char *result = NULL;
	size_t i = 0, j = 0;

	while (key[i] != ':')
		i++;

	result = malloc((i + 1) * sizeof(char));

	for (j = 0; j < i; j++)
		result[j] = key[j];

	result[j] = '\0';

	return (result);
}

/**
 * is_number - Validate if a string can be converted to a number.
 *
 * @str: String to valdidate.
 *
 * Return: Return 1 if the string contain only numbers, 0 otherwise.
 */

int is_number(char *str)
{
	int i = 0, len = strlen(str);

	while (str[i])
	{
		if (!(str[i] <= '9' && str[i] >= '0'))
			break;
		i++;
	}

	if (i == len)
		return (1);

	return (0);
}
