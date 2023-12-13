#include "main.h"

/**
 * get_builtin - The Entry Point.
 * Description - builtin that passes the command in the arg.
 * @cmd: the command.
 * Return: function pointer of the builtin command.
 */

int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int m;

	for (m = 0; builtin[m].name; m++)
	{
		if (_strcmp(builtin[m].name, cmd) == 0)
			break;
	}

	return (builtin[m].f);
}
