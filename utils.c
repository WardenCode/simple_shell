#include "main.h"

/**
 * validate_slash - Validate if the command have a slash
 * if not have that slash add it
 *
 * @cmd: Command.
 *
 * @holder: Contains a copy of the path.
 *
 * Return: Add a slash to the end
 */

char *validate_slash(char *cmd, char *holder)
{
	char *arg = NULL, *result = NULL;

	if (cmd[0] != '/')
	{
		arg = str_concat("/", cmd);
		result = str_concat(holder, arg);
		free(arg);
	}
	else
	{
		result = str_concat(holder, cmd);
	}
	return (result);
}

/**
 * find_char - Search a char inside of a str
 *
 * @str: String to search a char.
 *
 * @character: char to search in the str.
 *
 * Return: A pointer to the string before the char
 * if not find that char return the str completed.
 */

char *find_char(char *str, char character)
{
	char *result = NULL;
	size_t i = 0, j = 0;
	int flag = 0;

	while (str[i] != '\0')
	{
		if (str[i] == character)
		{
			flag = 1;
			break;
		}
		i++;
	}

	if (flag == 1 && str[i] != '\0')
		return (NULL);

	result = malloc((i + 1) * sizeof(char));
	if (!result)
		return (NULL);

	for (j = 0; j < i; j++)
		result[j] = str[j];

	result[j] = '\0';

	free(str);
	return (result);
}

/**
 * display_path - Display in the terminal the path.
 *
 * Return: Void.
 */

void display_path(void)
{
	char *path = NULL, *address = NULL;
	int i = 0, size = 0;

	path = getenv("PATH");
	size = strlen(path);
	while (path[i])
	{
		if (i > size)
			break;
		address = find_char(&path[i], ':');
		printf("%s\n", address);
		i += (strlen(address) + 1);
		free(address);
	}
}

/**
 * str_concat - Concatenate two strings in a new pointer
 *
 * @s1: String one.
 *
 * @s2: String two.
 *
 * Return: If success return a pointer with the concat otherwise null.
 */

char *str_concat(char *s1, char *s2)
{
	char *final_str = NULL;
	int size1 = 0, size2 = 0, total_size = 0, i = 0;

	size1 = strlen(s1);
	size2 = strlen(s2);

	total_size = size1 + size2 + 1;
	final_str = malloc(total_size * sizeof(char));
	if (!final_str)
		return (NULL);

	for (i = 0; i < total_size; i++)
	{
		if (size1 && i < size1)
			final_str[i] = s1[i];
		if (i >= size1 && s2)
			final_str[i] = s2[i - size1];
	}

	return (final_str);
}
