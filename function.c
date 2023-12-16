#include "shell.h"

/**
 * _setenv - the entry point.
 * Description - function that sets or update an environ var.
 * @name: environment variable.
 * @value: assigned value environment variable.
 * @overwrite: Flag indicating whether to overwrite an existing value (0 or 1).
 * Return: Always 0 on success, otherwise -1 on failure.
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	char *m, *v;

	/* Check if name or value is NULL */
	if (name == NULL || value == NULL)
	{
		fprintf(stderr, "Error: Name or value cannot be NULL.\n");
		return (-1);
	}

	/* Check if overwrite is a valid value (0 or 1) */
	if (overwrite != 0 && overwrite != 1)
	{
		fprintf(stderr, "Error: Overwrite must be 0 or 1.\n");
		return (-1);
	}

	m = v_getenv(name);
	if (m != NULL)
	{
		if (overwrite != 0)
			_unsetenv(name);
		else
			return (0);
	}

	v = malloc(strlen(name) + strlen(value) + 2);
	if (v == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		return (-1);
	}

	sprintf(v, "%s=%s", name, value);
	if (putenv(v) != 0)
	{
		fprintf(stderr, "Error: Unable to set environment variable.\n");
		safefree(v);
		return (-1);
	}
	return (0);
}

/**
 * _unsetenv - the entry point.
 * Description - function that removes an environment variable.
 * @name: remove environment variable.
 * Return: Always 0 on success, Otherwise -1 on failure.
 */

int _unsetenv(const char *name)
{
	size_t nl;
	char **c, **n, **e;

	if (name == NULL) /* Check if input name is NULL */
	{
		fprintf(stderr, "Error: Input name cannot be NULL.\n");
		return (-1);
	}

	if (v_getenv(name) == NULL) /* Check if the environment variable exists */
	{
		fprintf(stderr, "Error: Environment variable %s does not exist.\n", name);
		return (-1);
	}

	nl = _strlen(name);
	for (e = environ; *e != NULL; ++e)
	{
		/* Check if the current env. variable matches the specified name */
		if (_strncmp(*e, name, nl) == 0 && (*e)[nl] == '=')
		{
			c = e;
			n = e + 1;
			/* Shift the remaining env. variables to remove the unset one */
			while (*c != NULL)
			{
				*c = *n;
				++c;
				++n;
			}
			return (0);
		}
	}
	fprintf(stderr, "Error: Unable to find environment variable %s.\n", name);
	return (-1);
}


/**
 * exit_shell - the entry point.
 * Description - function that handles exiting the shell
 * with a specified exit code.
 * @lsh: shell structure pointer.
 * @func: Function pointer to the free_on_exit function.
 * Return: the exit code.
 */

int exit_shell(shell_t *lsh, void (*func)(const char *format, ...))
{
	int ec;

	if (lsh->tokenized_commands)
	{
		lsh->exit_status = lsh->tokenized_commands[1];
	}
	else
	{
		lsh->exit_status =  NULL;
	}

	ec = lsh->exit_code;

	if (lsh->exit_status == NULL)
	{
		func("upttt", lsh->user_input, &lsh->path_list, &lsh->tokens,
		&lsh->tokenized_commands, &lsh->command_array);
		safefree(lsh);
		exit(ec);
	}

	if (_isalpha(*lsh->exit_status) || atoi(lsh->exit_status) < 0
	|| *lsh->exit_status == '-')
	{
		dprintf(STDERR_FILENO, "%s: %lu: exit: Illegal number: %s\n",
		lsh->prog_name, lsh->cmd_count, lsh->exit_status);
		return (2);
	}

	ec = atoi(lsh->exit_status);
	func("upttt", lsh->user_input, &lsh->path_list, &lsh->tokens,
	&lsh->tokenized_commands, &lsh->command_array);
	safefree(lsh);
	exit(ec);
}

/**
 * _printenv - the entry point.
 * Description - function that prints the current environment variables.
 */

void _printenv(void)
{
	char **e;

	for (e = environ; *e != NULL; e++)
	{
		printf("%s\n", *e);
	}
}
