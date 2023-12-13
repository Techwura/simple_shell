#include "main.h"

/**
 * exec_line - The Entry Point.
 * Description - finds builtins and commands.
 * @datash: args - data relevant.
 * Return: Always 1 on success.
 */

int exec_line(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_exec(datash));
}
