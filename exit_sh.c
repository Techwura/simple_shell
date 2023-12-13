#include "main.h"

/**
 * exit_shell - The Entry Point.
 * Description -exits the shell.
 * @datash: data relevant (status and args).
 * Return: Always 0 on success.
 */

int exit_shell(data_shell *datash)
{
	unsigned int u;
	int id;
	int sl;
	int b;

	if (datash->args[1] != NULL)
	{
		u = _atoi(datash->args[1]);
		id = _isdigit(datash->args[1]);
		sl = _strlen(datash->args[1]);
		b = u > (unsigned int)INT_MAX;
		if (!id || sl > 10 || b)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (u % 256);
	}
	return (0);
}
