
#include "main.h"

/**
 * rev_string - The Entry Point.
 * Description - reverses a string.
 * @s: the input string.
 * Return: .
 */

void rev_string(char *s)
{
	int c = 0, m, n;
	char *str, t;

	while (c >= 0)
	{
		if (s[c] == '\0')
			break;
		c++;
	}
	str = s;

	for (m = 0; m < (c - 1); m++)
	{
		for (n = m + 1; n > 0; n--)
		{
			t = *(str + n);
			*(str + n) = *(str + (n - 1));
			*(str + (n - 1)) = t;
		}
	}
}
