#include "main.h"

/**
 * is_cdir - The Entry Point.
 * Description - checks ":" if is in the current directory.
 * @path: the type char pointer char.
 * @i: the type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */

int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - The Entry Point.
 * Description - locates a command.
 * @cmd: the command name.
 * @_environ: the environ variable.
 * Return: location of the command.
 */

char *_which(char *cmd, char **_environ)
{
	char *p, *pp, *tp, *d;
	int ld, lc, m;
	struct stat st;

	p = _getenv("PATH", _environ);
	if (p)
	{
		pp = _strdup(p);
		lc = _strlen(cmd);
		tp = _strtok(pp, ":");
		m = 0;
		while (tp != NULL)
		{
			if (is_cdir(p, &m))
				if (stat(cmd, &st) == 0)
					return (cmd);
			ld = _strlen(tp);
			d = malloc(ld + lc + 2);
			_strcpy(d, tp);
			_strcat(d, "/");
			_strcat(d, cmd);
			_strcat(d, "\0");
			if (stat(d, &st) == 0)
			{
				free(pp);
				return (d);
			}
			free(d);
			tp = _strtok(NULL, ":");
		}
		free(pp);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - The Entry Point.
 * Description - determines if is an executable.
 * @datash: the data structure.
 * Return: 0 if is not an executable, otherwise number if it does.
 */

int is_executable(data_shell *datash)
{
	struct stat st;
	int m;
	char *p;

	p = datash->args[0];
	for (m = 0; p[m]; m++)
	{
		if (p[m] == '.')
		{
			if (p[m + 1] == '.')
				return (0);
			if (p[m + 1] == '/')
				continue;
			else
				break;
		}
		else if (p[m] == '/' && m != 0)
		{
			if (p[m + 1] == '.')
				continue;
			m++;
			break;
		}
		else
			break;
	}
	if (m == 0)
		return (0);

	if (stat(p + m, &st) == 0)
	{
		return (m);
	}
	get_error(datash, 127);
	return (-1);
}

/**
 * check_error_cmd - The Entry Point.
 * Description - verifies if user has permissions to access.
 * @dir: the destination directory.
 * @datash: the data structure.
 * Return: 1 == error, Otherwise 0.
 */

int check_error_cmd(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - The Entry Point.
 * Description - executes command lines.
 * @datash: data relevant (args and input).
 * Return: Always 1 on success.
 */

int cmd_exec(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int s;
	int e;
	char *dir;
	(void) wpd;

	e = is_executable(datash);
	if (e == -1)
		return (1);
	if (e == 0)
	{
		dir = _which(datash->args[0], datash->_environ);
		if (check_error_cmd(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (e == 0)
			dir = _which(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + e, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &s, WUNTRACED);
		} while (!WIFEXITED(s) && !WIFSIGNALED(s));
	}

	datash->status = s / 256;
	return (1);
}
