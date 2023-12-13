#include "shell.h"

/**
 * handle_line - The Entry Point.
 * Description - Partitions a line read from standard input as needed.
 * @line: pointer to a line read from standard input.
 * @read: length of line.
 */

void handle_line(char **line, ssize_t read)
{
	char *ol, *nl;
	char p, c, n;
	size_t i, j;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;
	nl = malloc(new_len + 1);
	if (!nl)
		return;
	j = 0;
	ol = *line;
	for (i = 0; ol[i]; i++)
	{
		c = ol[i];
		n = ol[i + 1];
		if (i != 0)
		{
			p = ol[i - 1];
			if (c == ';')
			{
				if (n == ';' && p != ' ' && p != ';')
				{
					nl[j++] = ' ';
					nl[j++] = ';';
					continue;
				}
				else if (p == ';' && n != ' ')
				{
					nl[j++] = ';';
					nl[j++] = ' ';
					continue;
				}
				if (p != ' ')
					nl[j++] = ' ';
				nl[j++] = ';';
				if (n != ' ')
					nl[j++] = ' ';
				continue;
			}
			else if (c == '&')
			{
				if (n == '&' && p != ' ')
					nl[j++] = ' ';
				else if (p == '&' && n != ' ')
				{
					nl[j++] = '&';
					nl[j++] = ' ';
					continue;
				}
			}
			else if (c == '|')
			{
				if (n == '|' && p != ' ')
					nl[j++]  = ' ';
				else if (p == '|' && n != ' ')
				{
					nl[j++] = '|';
					nl[j++] = ' ';
					continue;
				}
			}
		}
		else if (c == ';')
		{
			if (i != 0 && ol[i - 1] != ' ')
				nl[j++] = ' ';
			nl[j++] = ';';
			if (n != ' ' && n != ';')
				nl[j++] = ' ';
			continue;
		}
		nl[j++] = ol[i];
	}
	nl[j] = '\0';

	free(*line);
	*line = nl;
}

/**
 * get_new_len - The Entry Point.
 * Description - Gets the new length of a line partitioned
 * by ";", "||", "&&&", or "#".
 * @line: line to be checked.
 * Return: new length of line.
 */

ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t nl = 0;
	char c, n;

	for (i = 0; line[i]; i++)
	{
		c = line[i];
		n = line[i + 1];
		if (c == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (c == ';')
			{
				if (n == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					nl += 2;
					continue;
				}
				else if (line[i - 1] == ';' && n != ' ')
				{
					nl += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					nl++;
				if (n != ' ')
					nl++;
			}
			else
				logical_ops(&line[i], &nl);
		}
		else if (c == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				nl++;
			if (n != ' ' && n != ';')
				nl++;
		}
		nl++;
	}
	return (nl);
}

/**
 * logical_ops - The Entry Point.
 * Description - Checks a line for logical operators "||" or "&&".
 * @line: pointer to the char to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */

void logical_ops(char *line, ssize_t *new_len)
{
	char p, c, n;

	p = *(line - 1);
	c = *line;
	n = *(line + 1);

	if (c == '&')
	{
		if (n == '&' && p != ' ')
			(*new_len)++;
		else if (p == '&' && n != ' ')
			(*new_len)++;
	}
	else if (c == '|')
	{
		if (n == '|' && p != ' ')
			(*new_len)++;
		else if (p == '|' && n != ' ')
			(*new_len)++;
	}
}
