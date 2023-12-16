#include "shell.h"

/**
 * _strdup - the entry point.
 * Decription - function that returns a pointer to a newly
 * allocated space in memory,
 * @str: the string.
 * Return: duplicated string.
 */

char *_strdup(char *str)
{
	size_t m, n = 0;
	char *s;
	char *t;

	/* is the string empty? */
	if (str == NULL)
		return (NULL); /* ah! it is, return NULL */

	/* Create a temporary pointer to keep original string unchanged */
	t = str;

	while (*t)
	{
		t++;
		n++;
	}
	n += 1; /* Add 1 for the null terminator */

	s = (char *)malloc(n * sizeof(char));
	if (s == NULL)
		return (NULL); /* Oops, mem. allocation failed */

	for (m = 0; m < n; ++m)
		s[m] = str[m];

	return (s); /* return pointer to duplicated string */
}


/**
 * _strchr - the entry point.
 * Decription - function that locates a character in a string.
 * @str: the string.
 * @c: the character to be located.
 * Return: @s.
 */

char *_strchr(char *str, char c)
{
	/* is the string empty? */
	if (str == NULL)
		return (NULL); /* it is, return NULL */

	while (*str != '\0')
	{
		if (*str == c)
		{
			/* return pointer to matched char */
			return (str);
		}
		str++;
	}

	if (c == '\0')
		return (str);

	return (NULL);
}


/**
 * _strncmp - the entry point.
 * Description - function that compares two strings up to a specified len.
 * @str1: 1st string.
 * @str2: 2nd string.
 * @n: The maximum number of char to compare.
 * Return: 0 == specified length, otherwise
 * the difference between the first non-matching characters.
 */

int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t m = 0;

	while (m < n && (str1[m] != '\0' || str2[m] != '\0'))
	{
		if (str1[m] != str2[m])
		{
			return ((int)(unsigned char)str1[m] - (int)(unsigned char)str2[m]);
		}
		++m;
	}

	return (0);
}

/**
 * _strlen - the entry point.
 * Description - function that returns the len of a string.
 * @s: the parameter.
 * Return: string length.
 */

int _strlen(const char *s)
{
	int c = 0;

	while (*s != '\0')
	{
		s++;
		c++;
	}
	return (c);
}
