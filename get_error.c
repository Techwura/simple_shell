#include "main.h"

/**
 * get_error - The Entry Point.
 * Description - calls the error according the builtin, syntax or permission.
 * @datash: the arguments data structure.
 * @eval: the error value.
 * Return: error.
 */

int get_error(data_shell *datash, int eval)
{
	char *e;

	switch (eval)
	{
	case -1:
		e = error_env(datash);
		break;
	case 126:
		e = error_path_126(datash);
		break;
	case 127:
		e = error_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			e = error_exit_shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			e = error_get_cd(datash);
		break;
	}

	if (e)
	{
		write(STDERR_FILENO, e, _strlen(e));
		free(e);
	}

	datash->status = eval;
	return (eval);
}
