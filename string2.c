#include "main.h"

/**
 * _strdup - The Entry Point.
 * Description - duplicates a str in the heap memory.
 * @s: Type char pointer string.
 * Return: the duplicated string.
 */

char *_strdup(const char *s)
{
	char *n;
	size_t l;

	l = _strlen(s);
	n = malloc(sizeof(char) * (l + 1));
	if (n == NULL)
		return (NULL);
	_memcpy(n, s, l + 1);
	return (n);
}

/**
 * _strlen - The Entry Point.
 * Description - Returns the length of a string.
 * @s: Type char pointer.
 * Return: Always 0.
 */

int _strlen(const char *s)
{
	int l;

	for (l = 0; s[l] != 0; l++)
	{
	}
	return (l);
}

/**
 * cmp_chars - The Entry Point.
 * Description - compare chars of strings.
 * @str: the input string.
 * @delim: the delimiter.
 * Return: 1 on equals, Otherwise 0.
 */

int cmp_chars(char str[], const char *delim)
{
	unsigned int m, n, k;

	for (m = 0, k = 0; str[m]; m++)
	{
		for (n = 0; delim[n]; n++)
		{
			if (str[m] == delim[n])
			{
				k++;
				break;
			}
		}
	}
	if (m == k)
		return (1);
	return (0);
}

/**
 * _strtok - The Entry Point
 * Description - splits a string by some delimiter.
 * @str: the input string.
 * @delim: the delimiter.
 * Return: the string splitted.
 */

char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *ss;
	unsigned int m, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; /*Store first address*/
		m = _strlen(str);
		str_end = &str[m]; /*Store last address*/
	}
	ss = splitted;
	if (ss == str_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != ss)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (m = 0; delim[m]; m++)
		{
			if (*splitted == delim[m])
			{
				*splitted = '\0';
				if (splitted == ss)
					ss++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (ss);
}

/**
 * _isdigit - The Entry Point.
 * Description - defines if string passed is a number.
 * @s: the input string.
 * Return: 1 if string is a number. Otherwise, 0.
 */

int _isdigit(const char *s)
{
	unsigned int m;

	for (m = 0; s[m]; m++)
	{
		if (s[m] < 48 || s[m] > 57)
			return (0);
	}
	return (1);
}
