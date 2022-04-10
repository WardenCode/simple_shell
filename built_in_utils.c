#include "main.h"

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
