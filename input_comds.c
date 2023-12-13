#include "shell.h"

/**
 * get_args - The Entry Point.
 * Description - Gets a command from standard input.
 * @line: buffer to store the command.
 * @exe_ret: return value of the last executed command.
 * Return: a pointer to the stored command, otherwise NULL -
 * if an error occurs - NULL.
 */

char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t r;
	char *p = "$ ";

	if (line)
		free(line);

	r = _getline(&line, &n, STDIN_FILENO);
	if (r == -1)
		return (NULL);
	if (r == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, p, 2);
		return (get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_args - The Entry Point.
 * Description - Partitions operators from commands and calls them.
 * @args: array of arguments.
 * @front: double pointer to the beginning of arguments.
 * @exe_ret: return value of the parent process' last executed command.
 * Return: return value of the last executed command.
 */

int call_args(char **args, char **front, int *exe_ret)
{
	int r, i;

	if (!args[0])
		return (*exe_ret);
	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			r = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (r);
			}
		}
		else if (_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			r = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (r);
			}
		}
	}
	args = replace_aliases(args);
	r = run_args(args, front, exe_ret);
	return (r);
}

/**
 * run_args - The Entry Point.
 * Description - Calls the execution of a command.
 * @args: array of arguments.
 * @front: double pointer to the beginning of arguments.
 * @exe_ret: return value of the parent process' last executed command.
 * Return: return value of the last executed command.
 */

int run_args(char **args, char **front, int *exe_ret)
{
	int r, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		r = builtin(args + 1, front);
		if (r != EXIT)
			*exe_ret = r;
	}
	else
	{
		*exe_ret = execute(args, front);
		r = *exe_ret;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (r);
}

/**
 * handle_args - The Entry Point.
 * Description - Gets, calls, and runs the execution of a command.
 * @exe_ret: return value of the parent process' last executed command.
 * Return: when end-of-file is read - END_OF_FILE (-2),
 * when input cannot be tokenized - -1,
 * Otherwise, exit value of the last executed command.
 */

int handle_args(int *exe_ret)
{
	int r = 0, i;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (r);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			r = call_args(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (r);
}

/**
 * check_args - The Entry Point.
 * Description - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2,
 * Otherwise always 0.
 */

int check_args(char **args)
{
	size_t m;
	char *c, *n;

	for (m = 0; args[m]; m++)
	{
		c = args[m];
		if (c[0] == ';' || c[0] == '&' || c[0] == '|')
		{
			if (m == 0 || c[1] == ';')
				return (create_error(&args[m], 2));
			n = args[m + 1];
			if (n && (n[0] == ';' || n[0] == '&' || n[0] == '|'))
				return (create_error(&args[m + 1], 2));
		}
	}
	return (0);
}
