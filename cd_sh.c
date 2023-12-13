#include "main.h"

/**
 * cd_sh - The Entry Point.
 * Description - Function that changes current directory.
 * @datash: data relevant.
 * Return: Always 1 on success.
 */

int cd_sh(data_shell *datash)
{
	char *d;
	int ih, ih2, id;

	d = datash->args[1];

	if (d != NULL)
	{
		ih = _strcmp("$HOME", d);
		ih2 = _strcmp("~", d);
		id = _strcmp("--", d);
	}

	if (d == NULL || !ih || !ih2 || !id)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", d) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", d) == 0 || _strcmp("..", d) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
