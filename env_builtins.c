#include "main.h"

/**
 * copy_info - The Entry Point.
 * Description - Function that copies info to create a new env or alias.
 * @name: the env or alias name.
 * @value: the env or alias value.
 * Return: new env or alias.
 */

char *copy_info(char *name, char *value)
{
	char *new;
	int ln, lv, l;

	ln = _strlen(name);
	lv = _strlen(value);
	l = ln + lv + 2;
	new = malloc(sizeof(char) * (l));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - The Entry Poiint.
 * Description - Function that sets an environment variable.
 * @name: the name of the env variable.
 * @value: the value of the env variable.
 * @datash: environ - the data structure.
 * Return: .
 */

void set_env(char *name, char *value, data_shell *datash)
{
	int m;
	char *ve, *ne;

	for (m = 0; datash->_environ[m]; m++)
	{
		ve = _strdup(datash->_environ[m]);
		ne = _strtok(ve, "=");
		if (_strcmp(ne, name) == 0)
		{
			free(datash->_environ[m]);
			datash->_environ[m] = copy_info(ne, value);
			free(ve);
			return;
		}
		free(ve);
	}

	datash->_environ = _reallocdp(datash->_environ, m, sizeof(char *) * (m + 2));
	datash->_environ[m] = copy_info(name, value);
	datash->_environ[m + 1] = NULL;
}

/**
 * _setenv - The Entry Point.
 * Description - Function that compares env variables names with
 * the name passed.
 * @datash: data relevant (env name and env value).
 * Return: Always 1 on success.
 */

int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - The Entry Point.
 * Description - Function that deletes a environment variable.
 * @datash: env name - data relevant.
 * Return: Always 1 on success.
 */

int _unsetenv(data_shell *datash)
{
	char **re;
	char *ve, *ne;
	int m, n, k;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	k = -1;
	for (m = 0; datash->_environ[m]; m++)
	{
		ve = _strdup(datash->_environ[m]);
		ne = _strtok(ve, "=");
		if (_strcmp(ne, datash->args[1]) == 0)
		{
			k = m;
		}
		free(ve);
	}
	if (k == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	re = malloc(sizeof(char *) * (m));
	for (m = n = 0; datash->_environ[m]; m++)
	{
		if (m != k)
		{
			re[n] = datash->_environ[m];
			n++;
		}
	}
	re[n] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = re;
	return (1);
}
