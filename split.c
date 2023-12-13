#include "main.h"

/**
 * swap_char - The Entry Point.
 * Description - swaps | and & for non-printed chars.
 * @input: the input string.
 * @bool: the type of swap.
 * Return: the swapped string.
 */

char *swap_char(char *input, int bool)
{
	int m;

	if (bool == 0)
	{
		for (m = 0; input[m]; m++)
		{
			if (input[m] == '|')
			{
				if (input[m + 1] != '|')
					input[m] = 16;
				else
					m++;
			}

			if (input[m] == '&')
			{
				if (input[m + 1] != '&')
					input[m] = 12;
				else
					m++;
			}
		}
	}
	else
	{
		for (m = 0; input[m]; m++)
		{
			input[m] = (input[m] == 16 ? '|' : input[m]);
			input[m] = (input[m] == 12 ? '&' : input[m]);
		}
	}
	return (input);
}

/**
 * add_nodes - The Entry Point.
 * Description - add separators and command lines in the lists.
 * @head_s: the separator list head.
 * @head_l: the command lines list head.
 * @input: the input string.
 * Return: .
 */

void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int m;
	char *l;

	input = swap_char(input, 0);

	for (m = 0; input[m]; m++)
	{
		if (input[m] == ';')
			add_sep_node_end(head_s, input[m]);

		if (input[m] == '|' || input[m] == '&')
		{
			add_sep_node_end(head_s, input[m]);
			m++;
		}
	}

	l = _strtok(input, ";|&");
	do {
		l = swap_char(l, 1);
		add_line_node_end(head_l, l);
		l = _strtok(NULL, ";|&");
	} while (l != NULL);

}

/**
 * go_next - The Entry Point.
 * Description - go to the next command line stored.
 * @list_s: the separator list.
 * @list_l: the command line list.
 * @datash: data structure.
 * Return: .
 */

void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep;
	sep_list *ls;
	line_list *ll;

	loop_sep = 1;
	ls = *list_s;
	ll = *list_l;

	while (ls != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls->separator == '&' || ls->separator == ';')
				loop_sep = 0;
			if (ls->separator == '|')
				ll = ll->next, ls = ls->next;
		}
		else
		{
			if (ls->separator == '|' || ls->separator == ';')
				loop_sep = 0;
			if (ls->separator == '&')
				ll = ll->next, ls = ls->next;
		}
		if (ls != NULL && !loop_sep)
			ls = ls->next;
	}

	*list_s = ls;
	*list_l = ll;
}

/**
 * split_commands - The Entry Point.
 * Description - splits command lines according to the
 * separators ;, | and &, and executes them.
 * @datash: the data structure.
 * @input: the input string.
 * Return: 0 to exit, 1 to continue.
 */

int split_commands(data_shell *datash, char *input)
{

	sep_list *hs, *ls;
	line_list *hl, *ll;
	int l;

	hs = NULL;
	hl = NULL;

	add_nodes(&hs, &hl, input);

	ls = hs;
	ll = hl;

	while (ll != NULL)
	{
		datash->input = ll->line;
		datash->args = split_line(datash->input);
		l = exec_line(datash);
		free(datash->args);

		if (l == 0)
			break;

		go_next(&ls, &ll, datash);

		if (ll != NULL)
			ll = ll->next;
	}

	free_sep_list(&hs);
	free_line_list(&hl);

	if (l == 0)
		return (0);
	return (1);
}

/**
 * split_line - The Entry Point.
 * Description - tokenizes the input string.
 * @input: the input string.
 * Return: the string splitted.
 */

char **split_line(char *input)
{
	size_t bs;
	size_t m;
	char **tokens;
	char *token;

	bs = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bs));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (m = 1; token != NULL; m++)
	{
		if (m == bs)
		{
			bs += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, m, sizeof(char *) * bs);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[m] = token;
	}

	return (tokens);
}
