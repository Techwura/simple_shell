#include "shell.h"

/**
 * free_args - The Entry Point.
 * Description - Frees up the memory taken by args.
 * @args: null-terminated double pointer containing commands/args.
 * @front: double pointer to the beginning of args.
 */

void free_args(char **args, char **front)
{
	size_t m;

	for (m = 0; args[m] || args[m + 1]; m++)
		free(args[m]);

	free(front);
}

/**
 * get_pid - The Entry Point.
 * Description - Gets the current process ID.
 * Return: current process ID or NULL on failure.
 */

char *get_pid(void)
{
	size_t m = 0;
	char *b;
	ssize_t f;

	f = open("/proc/self/stat", O_RDONLY);
	if (f == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	b = malloc(120);
	if (!b)
	{
		close(f);
		return (NULL);
	}
	read(f, b, 120);
	while (b[m] != ' ')
		m++;
	b[m] = '\0';

	close(f);
	return (b);
}

/**
 * get_env_value - The Entry Point.
 * Description - Gets the value corresponding to an env var.
 * @beginning: The env var to search for.
 * @len: The length of the env var to search for.
 * Return: the value of the env var, otherwise an empty string -
 * if the variable is not found - an empty string.
 */

char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *r = NULL, *t, *v;

	v = malloc(len + 1);
	if (!v)
		return (NULL);
	v[0] = '\0';
	_strncat(v, beginning, len);

	var_addr = _getenv(v);
	free(v);
	if (var_addr)
	{
		t = *var_addr;
		while (*t != '=')
			t++;
		t++;
		r = malloc(_strlen(t) + 1);
		if (r)
			_strcpy(r, t);
	}

	return (r);
}

/**
 * variable_replacement - The Entry Point.
 * Description - Handles var replacement.
 * @line: double pointer containing the command and args.
 * @exe_ret: pointer to the return value of the last executed command.
 */

void variable_replacement(char **line, int *exe_ret)
{
	int m, k = 0, len;
	char *r = NULL, *ol = NULL, *nl;

	ol = *line;
	for (m = 0; ol[m]; m++)
	{
		if (ol[m] == '$' && ol[m + 1] &&
				ol[m + 1] != ' ')
		{
			if (ol[m + 1] == '$')
			{
				r = get_pid();
				k = m + 2;
			}
			else if (ol[m + 1] == '?')
			{
				r = _itoa(*exe_ret);
				k = m + 2;
			}
			else if (ol[m + 1])
			{
				/* extract the variable name to search for */
				for (k = m + 1; ol[k] &&
						ol[k] != '$' &&
						ol[k] != ' '; k++)
					;
				len = k - (m + 1);
				r = get_env_value(&ol[m + 1], len);
			}
			nl = malloc(m + _strlen(r)
					  + _strlen(&ol[k]) + 1);
			if (!line)
				return;
			nl[0] = '\0';
			_strncat(nl, ol, m);
			if (r)
			{
				_strcat(nl, r);
				free(r);
				r = NULL;
			}
			_strcat(nl, &ol[k]);
			free(ol);
			*line = nl;
			ol = nl;
			m = -1;
		}
	}
}
