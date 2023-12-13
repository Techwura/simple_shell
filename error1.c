
#include "main.h"

/**
 * strcat_cd - The Entry Point.
 * Description - function that concatenates the message for cd error.
 * @datash: directory - data relevant.
 * @msg: message to print.
 * @error: output message.
 * @ver_str: counter lines.
 * Return: error message.
 */

char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *ilf;

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, msg);
	if (datash->args[1][0] == '-')
	{
		ilf = malloc(3);
		ilf[0] = '-';
		ilf[1] = datash->args[1][1];
		ilf[2] = '\0';
		_strcat(error, ilf);
		free(ilf);
	}
	else
	{
		_strcat(error, datash->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - The Entry Point.
 * Description - error message for cd command in get_cd.
 * @datash: directory - data relevant.
 * Return: Error message.
 */

char *error_get_cd(data_shell *datash)
{
	int l, li;
	char *error, *v, *m;

	v = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		m = ": Illegal option ";
		li = 2;
	}
	else
	{
		m = ": can't cd to ";
		li = _strlen(datash->args[1]);
	}

	l = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	l += _strlen(v) + _strlen(m) + li + 5;
	error = malloc(sizeof(char) * (l + 1));

	if (error == 0)
	{
		free(v);
		return (NULL);
	}

	error = strcat_cd(datash, m, error, v);

	free(v);

	return (error);
}

/**
 * error_not_found - The Entry Point.
 * Description - generic error message for command not found.
 * @datash: couunter, arguments - data relevant.
 * Return: the rror message.
 */

char *error_not_found(data_shell *datash)
{
	int l;
	char *error;
	char *v;

	v = aux_itoa(datash->counter);
	l = _strlen(datash->av[0]) + _strlen(v);
	l += _strlen(datash->args[0]) + 16;
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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(v);
	return (error);
}

/**
 * error_exit_shell - The Entry Point.
 * Description - generic error message for exit in get_exit.
 * @datash: counter, arguments - data relevant.
 * Return: the error message.
 */

char *error_exit_shell(data_shell *datash)
{
	int l;
	char *error;
	char *v;

	v = aux_itoa(datash->counter);
	l = _strlen(datash->av[0]) + _strlen(v);
	l += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(v);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, v);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, datash->args[1]);
	_strcat(error, "\n\0");
	free(v);

	return (error);
}
