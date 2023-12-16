#include "shell.h"

/**
 * execute_builtin - the entry point.
 * Description - function that executes built-in shell commands.
 * @lsh: command tokens.
 * Return: the exit status = 'exit' command is executed,
 * otherwise 18.
 */

int execute_builtin(shell_t *lsh)
{
	if (!_strcmp(lsh->tokenized_commands[0], "exit"))
	{
		return (exit_shell(lsh, free_up));
	}
	else if (!_strcmp(lsh->tokenized_commands[0], "setenv"))
	{
		if (lsh->tokenized_commands[1] && lsh->tokenized_commands[2])
			return (_setenv(lsh->tokenized_commands[1], lsh->tokenized_commands[2], 1));
		return (1);
	}
	else if (!_strcmp(lsh->tokenized_commands[0], "unsetenv"))
	{
		if (lsh->tokenized_commands[1])
		{
			return (_unsetenv(lsh->tokenized_commands[1]));
		}
	}
	else if (!_strcmp(lsh->tokenized_commands[0], "printenv") ||
			!_strcmp(lsh->tokenized_commands[0], "env"))
	{
		_printenv();
		return (0);
	}
	return (18);
}
