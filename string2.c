#include "shell.h"

/**
 * free_string - the entry point.
 * Description - function that frees memory allocated
 * for an array of strings.
 * @string_array: array of strings.
 */

void free_string(char ***string_array)
{
	int m = 0;
	char **a;

	if (string_array == NULL || (*string_array) == NULL)
		return;

	a = *string_array;

	for (a = 0; a[m] != NULL; m++)
	{
		safefree(a[m]);
	}

	safefree(a);
	*string_array = NULL;
}

/**
 * _strncpy - the entry point.
 * Description - function that copies up to n char from the
 * source string to the dest.
 * @dest: dest string.
 * @src: source string.
 * @n: max number of char to copy.
 * Return: dest string.
 */

char *_strncpy(char *dest, const char *src, int n)
{
	int m = 0;

	while (m < n && src[m] != '\0')
	{
		dest[m] = src[m];
		m++;
	}

	while (m < n)
	{
		dest[m] = '\0';
		m++;
	}

	return (dest);
}


/**
 * _isalpha - the entry point.
 * Description - function that checks for alphabetic char.
 * @c: the para value.
 * Return: always 1 if c is a letter, lowercase or uppercase.
 */

int _isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
	{
		return (1);
	}
	else
	{
		return (0);
	}

	return (0);
}

/**
 * _strcmp - the entry point.
 * Description - function that compares two strings.
 * @s1: 1st string.
 * @s2: 2nd string.
 * Return: 0 == @s1 and @s2, a negative value if @s1 is
 * < @s2, a positive value if @s1 > @s2.
 */

int _strcmp(char *s1, char *s2)
{
	int m = 0;

	while (s1[m] != '\0' && s2[m] != '\0')
	{
		if (s1[m] != s2[m])
		{
			return (s1[m] -  s2[m]);
		}
		m++;
	}

	return (0);
}
