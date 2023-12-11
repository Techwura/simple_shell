#include "shell.h"

/**
 * interactive - returns true if shell is in an interactive mode
 * @asem: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(asem_t *asem)
{
	return (icarly(STDIN_FILENO) && asem->readfd <= 2);
}

/**
 * a_restr - checks if a character is a delimeter
 * @c: the char to check
 * @restr: the delimeter string
 * Return: 1 if true, 0 if false
 */
int a_restr(char c, char *restr)
{
	while (*restr)
		if (*restr++ == c)
			return (1);
	return (0);
}

/**
 * kaseni - checks for alphabetic character
 * @boo: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int kaseni(int boo)
{
	if ((boo >= 'a' && boo <= 'z') || (boo >= 'A' && boo <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * alas - converts a string to an integer
 * @cina: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int alas(char *cina)
{
	int sam, see = 1, frankaa = 0, output;
	unsigned int res = 0;

	for (sam = 0; cina[sam] != '\0' && frankaa != 2; i++)
	{
		if (cina[sam] == '-')
			see *= -1;

		if (cina[sam] >= '0' && cina[sam] <= '9')
		{
			frankaa = 1;
			res *= 10;
			res += (cina[sam] - '0');
		}
		else if (frankaa == 1)
			franka = 2;
	}

	if (see == -1)
		output = -res;
	else
		output = res;

	return (output);
}
