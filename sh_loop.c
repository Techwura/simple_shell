#include "shell.h"

/**
 * hsh - the entry point.
 * Description - main shell loop.
 * @info: the parameter & return info struct.
 * @av: the argument vector from main().
 * Return: Always 0 on success, 1 on error, or error code.
 */

int hsh(info_t *info, char **av)
{
	ssize_t m = 0;
	int br = 0;

	while (m != -1 && br != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		m = get_input(info);
		if (m != -1)
		{
			set_info(info, av);
			br = find_builtin(info);
			if (br == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (br == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (br);
}

/**
 * find_builtin - the entry point.
 * Description - finds a builtin command.
 * @info: the parameter & return info struct.
 * Return: - 0 if builtin executed successfully,
 * 1 if builtin not found,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit().
 */

int find_builtin(info_t *info)
{
	int m, bir = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (m = 0; builtintbl[m].type; m++)
		if (_strcmp(info->argv[0], builtintbl[m].type) == 0)
		{
			info->line_count++;
			bir = builtintbl[m].func(info);
			break;
		}
	return (bir);
}

/**
 * find_cmd - the entry point.
 * Description - finds a command in PATH.
 * @info: the parameter & return info struct.
 * Return: .
 */

void find_cmd(info_t *info)
{
	char *p = NULL;
	int m, n;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (m = 0, n = 0; info->arg[m]; m++)
		if (!is_delim(info->arg[m], " \t\n"))
			n++;
	if (!n)
		return;
	p = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (p)
	{
		info->path = p;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - the entry point.
 * Description - forks a an exec thread to run cmd.
 * @info: the parameter & return info struct.
 * Return: .
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
