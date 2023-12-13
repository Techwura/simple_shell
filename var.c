#include "main.h"

/**
 * check_env - The Entry Point.
 * Description - checks if the typed variable is an env variable.
 * @h: the linked list head.
 * @in: the input string.
 * @data: the data structure.
 * Return: .
 */

void check_env(r_var **h, char *in, data_shell *data)
{
	int r, c, n, lv;
	char **_envr;

	_envr = data->_environ;
	for (r = 0; _envr[r]; r++)
	{
		for (n = 1, c = 0; _envr[r][c]; c++)
		{
			if (_envr[r][c] == '=')
			{
				lv = _strlen(_envr[r] + c + 1);
				add_rvar_node(h, n, _envr[r] + c + 1, lv);
				return;
			}

			if (in[n] == _envr[r][c])
				n++;
			else
				break;
		}
	}

	for (n = 0; in[n]; n++)
	{
		if (in[n] == ' ' || in[n] == '\t' || in[n] == ';' || in[n] == '\n')
			break;
	}

	add_rvar_node(h, n, NULL, 0);
}

/**
 * check_vars - The Entry Point.
 * Description - check if the typed variable is $$ or $?.
 * @h: the linked list head.
 * @in: the input string.
 * @st: the last status of the Shell.
 * @data: the data structure.
 * Return: .
 */

int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int m, lt, ld;

	lt = _strlen(st);
	ld = _strlen(data->pid);

	for (m = 0; in[m]; m++)
	{
		if (in[m] == '$')
		{
			if (in[m + 1] == '?')
				add_rvar_node(h, 2, st, lt), m++;
			else if (in[m + 1] == '$')
				add_rvar_node(h, 2, data->pid, ld), m++;
			else if (in[m + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[m + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[m + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[m + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[m + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + m, data);
		}
	}

	return (m);
}

/**
 * replaced_input - The Entry Point.
 * Description - replaces string into variables.
 * @head: the linked list head.
 * @input: the input string.
 * @new_input: the new replaced input string.
 * @nlen: the new length.
 * Return: the replaced string.
 */

char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *i;
	int m, n, k;

	i = *head;
	for (n = m = 0; m < nlen; m++)
	{
		if (input[n] == '$')
		{
			if (!(i->len_var) && !(i->len_val))
			{
				new_input[m] = input[n];
				n++;
			}
			else if (i->len_var && !(i->len_val))
			{
				for (k = 0; k < i->len_var; k++)
					n++;
				m--;
			}
			else
			{
				for (k = 0; k < i->len_val; k++)
				{
					new_input[m] = i->val[k];
					m++;
				}
				n += (i->len_var);
				m--;
			}
			i = i->next;
		}
		else
		{
			new_input[m] = input[n];
			n++;
		}
	}

	return (new_input);
}

/**
 * rep_var - The Entry Point.
 * Description - calls functions to replace string into vars.
 * @input: the input string.
 * @datash: the data structure.
 * Return: the replaced string.
 */

char *rep_var(char *input, data_shell *datash)
{
	r_var *h, *i;
	char *s, *ni;
	int ol, nl;

	s = aux_itoa(datash->status);
	h = NULL;

	ol = check_vars(&h, input, s, datash);

	if (h == NULL)
	{
		free(s);
		return (input);
	}

	i = h;
	nl = 0;

	while (i != NULL)
	{
		nl += (i->len_val - i->len_var);
		i = i->next;
	}

	nl += ol;

	ni = malloc(sizeof(char) * (nl + 1));
	ni[nl] = '\0';

	ni = replaced_input(&h, input, ni, nl);

	free(input);
	free(s);
	free_rvar_list(&h);

	return (ni);
}
