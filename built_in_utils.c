#include "main.h"

int number_of_tokens(char **tokens)
{
	int number = 0;

	while (tokens[number])
		number++;

	return (number);
}

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
