#include "main.h"

/**
 * get_len - The Entry Point.
 * Description - Get the length of a number.
 * @n: type integer number.
 * Return: lenght of a number.
 */

int get_len(int n)
{
	unsigned int m;
	int l = 1;

	if (n < 0)
	{
		l++;
		m = n * -1;
	}
	else
	{
		m = n;
	}
	while (m > 9)
	{
		l++;
		m = m / 10;
	}

	return (l);
}

/**
 * aux_itoa - The Entry Point.
 * Description - function converts int to string.
 * @n: type integer number.
 * Return: String.
 */

char *aux_itoa(int n)
{
	unsigned int m;
	int l = get_len(n);
	char *b;

	b = malloc(sizeof(char) * (l + 1));
	if (b == 0)
		return (NULL);

	*(b + l) = '\0';

	if (n < 0)
	{
		m = n * -1;
		b[0] = '-';
	}
	else
	{
		m = n;
	}

	l--;
	do {
		*(b + l) = (m % 10) + '0';
		m = m / 10;
		l--;
	}
	while (m > 0)
		;
	return (b);
}

/**
 * _atoi - The Entry Point.
 * Description - converts a string to an integer.
 * @s: the input string.
 * Return: integer.
 */

int _atoi(char *s)
{
	unsigned int c = 0, d = 0, a = 0, b = 1, m = 1, e;

	while (*(s + c) != '\0')
	{
		if (d > 0 && (*(s + c) < '0' || *(s + c) > '9'))
			break;

		if (*(s + c) == '-')
			b *= -1;

		if ((*(s + c) >= '0') && (*(s + c) <= '9'))
		{
			if (d > 0)
				m *= 10;
			d++;
		}
		c++;
	}

	for (e = c - d; e < c; e++)
	{
		a = a + ((*(s + e) - 48) * m);
		m /= 10;
	}
	return (a * b);
}
