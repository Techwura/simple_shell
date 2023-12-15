#include "shell.h"

/**
 * is_chain - the entry point.
 * Description - test if current char in buffer is a chain delimeter.
 * @info: the para struct.
 * @buf: the char buffer.
 * @p: address of current position in buf.
 * Return: 1 if chain delimeter, Otherwise 0.
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t m = *p;

	if (buf[m] == '|' && buf[m + 1] == '|')
	{
		buf[m] = 0;
		m++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[m] == '&' && buf[m + 1] == '&')
	{
		buf[m] = 0;
		m++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[m] == ';') /* found end of this command */
	{
		buf[m] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = m;
	return (1);
}

/**
 * check_chain - the entry point.
 * Description - checks we should continue chaining based on last status.
 * @info: para struct.
 * @buf: char buffer.
 * @p: address of current position in buf.
 * @i: starting position in buf.
 * @len: length of buf.
 * Return: .
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t m = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			m = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			m = len;
		}
	}
	*p = m;
}

/**
 * replace_alias - the entry point.
 * Description - replaces an aliases in the tokenized string.
 * @info: para struct.
 * Return: 1 if replaced, Otherwise 0.
 */

int replace_alias(info_t *info)
{
	int m;
	list_t *node;
	char *n;

	for (m = 0; m < 10; m++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		n = _strchr(node->str, '=');
		if (!n)
			return (0);
		n = _strdup(n + 1);
		if (!n)
			return (0);
		info->argv[0] = n;
	}
	return (1);
}

/**
 * replace_vars - the entry point.
 * Description - replaces vars in the tokenized string.
 * @info: para struct.
 * Return: 1 if replaced, Otherwise 0.
 */

int replace_vars(info_t *info)
{
	int m = 0;
	list_t *n;

	for (m = 0; info->argv[m]; m++)
	{
		if (info->argv[m][0] != '$' || !info->argv[m][1])
			continue;
		if (!_strcmp(info->argv[m], "$?"))
		{
			replace_string(&(info->argv[m]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[m], "$$"))
		{
			replace_string(&(info->argv[m]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		n = node_starts_with(info->env, &info->argv[m][1], '=');
		if (n)
		{
			replace_string(&(info->argv[m]),
					_strdup(_strchr(n->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[m], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - the entry point.
 * Description  - replaces string.
 * @old: address of old string.
 * @new: new string.
 * Return: Always 1 if replaced, 0 otherwise.
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

