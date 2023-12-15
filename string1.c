#include "shell.h"

/**
 * _strcpy - the entry point.
 * Description - copies a string.
 * @dest: the destination.
 * @src: the source.
 * Return: pointer to destination.
 */

char *_strcpy(char *dest, char *src)
{
	int m = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[m])
	{
		dest[m] = src[m];
		m++;
	}
	dest[m] = 0;
	return (dest);
}

/**
 * _strdup - the entry point.
 * Description - duplicates a string.
 * @str: the string to duplicate.
 * Return: pointer to the duplicated string.
 */

char *_strdup(const char *str)
{
	int m = 0;
	char *r;

	if (str == NULL)
		return (NULL);
	while (*str++)
		m++;
	r = malloc(sizeof(char) * (m + 1));
	if (!r)
		return (NULL);
	for (m++; m--;)
		r[m] = *--str;
	return (r);
}

/**
 * _puts - the entry point.
 * Description - prints an input string.
 * @str: the string to be printed.
 * Return: .
 */

void _puts(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		_putchar(str[m]);
		m++;
	}
}

/**
 * _putchar - the entry point.
 * Description - writes the char c to stdout.
 * @c: The char to print.
 * Return: Always 1 on success,Otherwise on error, -1 is returned,
 * and errno is set appropriately.
 */

int _putchar(char c)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(1, buf, m);
		m = 0;
	}
	if (c != BUF_FLUSH)
		buf[m++] = c;
	return (1);
}
