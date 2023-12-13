#include "main.h"

/**
 * cmp_env_name - The Entry Point.
 * Description - compares env variables names with the name passed.
 * @nenv: the name of the environ var.
 * @name: the name passed.
 * Return: 0 if not equal. Another number if they are.
 */

int cmp_env_name(const char *nenv, const char *name)
{
	int m;

	for (m = 0; nenv[m] != '='; m++)
	{
		if (nenv[m] != name[m])
		{
			return (0);
		}
	}

	return (m + 1);
}

/**
 * _getenv - The Entry Point.
 * Description - get an environ var.
 * @name: name of the environ var.
 * @_environ: the environ var.
 * Return: value of the environ var if is found.
 * Otherwise, returns NULL.
 */

char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int a, m;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	m = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (a = 0; _environ[a]; a++)
	{
		/* If name and env are equal */
		m = cmp_env_name(_environ[a], name);
		if (m)
		{
			ptr_env = _environ[a];
			break;
		}
	}

	return (ptr_env + m);
}

/**
 * _env - The Entry Point.
 * Description - prints the evironment variables.
 * @datash: the data relevant.
 * Return: Always 1 on success.
 */

int _env(data_shell *datash)
{
	int m, n;

	for (m = 0; datash->_environ[m]; m++)
	{

		for (n = 0; datash->_environ[m][n]; n++)
			;

		write(STDOUT_FILENO, datash->_environ[m], n);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
