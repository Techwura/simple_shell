#include "main.h"

/**
 * error_env - The Entry Point.
 * Description - error message for env in get_env.
 * @datash: counter, arguments - data relevant.
 * Return: error message.
 */

char *error_env(data_shell *datash)
{
	int l;
	char *error;
	char *v;
	char *m;

	v = aux_itoa(datash->counter);
	m = ": Unable to add/remove from environment\n";
	l = _strlen(datash->av[0]) + _strlen(v);
	l += _strlen(datash->args[0]) + _strlen(m) + 4;
	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(error);
		free(v);
		return (NULL);
	}

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, v);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, m);
	_strcat(error, "\0");
	free(v);

	return (error);
}

/**
 * error_path_126 - The Entry Point.
 * Description - error message for path and failure denied permission.
 * @datash: counter, arguments - data relevant.
 * Return: error string.
 */

char *error_path_126(data_shell *datash)
{
	int l;
	char *v;
	char *error;

	v = aux_itoa(datash->counter);
	l = _strlen(datash->av[0]) + _strlen(v);
	l += _strlen(datash->args[0]) + 24;
	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(error);
		free(v);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, v);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(v);
	return (error);
}
