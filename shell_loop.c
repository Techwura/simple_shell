#include "main.h"

/**
 * without_comment - The Entry Point.
 * Description - deletes comments from the input.
 * @in: the input string.
 * Return: the input without comments.
 */

char *without_comment(char *in)
{
	int m, u;

	u = 0;
	for (m = 0; in[m]; m++)
	{
		if (in[m] == '#')
		{
			if (m == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[m - 1] == ' ' || in[m - 1] == '\t' || in[m - 1] == ';')
				u = m;
		}
	}

	if (u != 0)
	{
		in = _realloc(in, m, u + 1);
		in[u] = '\0';
	}

	return (in);
}

/**
 * shell_loop - The Entry Point.
 * Description - Loop of shell.
 * @datash: data relevant (av, input, args).
 * Return: .
 */

void shell_loop(data_shell *datash)
{
	int l, i;
	char *input;

	l = 1;
	while (l == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i);
		if (i != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			l = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			l = 0;
			free(input);
		}
	}
}
