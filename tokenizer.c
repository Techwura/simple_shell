#include "shell.h"

/**
 * **strtow - the entry point.
 * DEscription - splits a string into words. Repeat delimiters are ignored.
 * @str: input string.
 * @d: delimiter string.
 * Return: a pointer to an array of strings, or NULL on failure.
 */

char **strtow(char *str, char *d)
{
	int a, b, c, m, n = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			n++;
	if (n == 0)
		return (NULL);
	s = malloc((1 + n) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < n; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			s[b][m] = str[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - the entry point.
 * Description - splits a string into words.
 * @str: the input string.
 * @d: the delimeter.
 * Return: a pointer to an array of strings, or NULL on failure.
 */

char **strtow2(char *str, char d)
{
	int a, b, c, m, n = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				(str[a] != d && !str[a + 1]) || str[a + 1] == d)
			n++;
	if (n == 0)
		return (NULL);
	s = malloc((1 + n) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < n; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			s[b][m] = str[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}
