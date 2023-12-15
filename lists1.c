#include "shell.h"

/**
 * list_len - The Entry Point.
 * Description - determines length of linked list.
 * @h: the 1st node pointer.
 * Return: size of list.
 */

size_t list_len(const list_t *h)
{
	size_t m = 0;

	while (h)
	{
		h = h->next;
		m++;
	}
	return (m);
}

/**
 * list_to_strings - the entry point.
 * Description - returns an array of strings of the list->str.
 * @head: the 1st node pointer.
 * Return: array of strings.
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t m = list_len(head), a;
	char **ss;
	char *s;

	if (!head || !m)
		return (NULL);
	ss = malloc(sizeof(char *) * (m + 1));
	if (!ss)
		return (NULL);
	for (m = 0; node; node = node->next, m++)
	{
		s = malloc(_strlen(node->str) + 1);
		if (!s)
		{
			for (a = 0; a < m; a++)
				free(ss[a]);
			free(ss);
			return (NULL);
		}
		s = _strcpy(s, node->str);
		ss[m] = s;
	}
	ss[m] = NULL;
	return (ss);
}

/**
 * print_list - the entry point.
 * Description - prints all elements of a list_t linked list.
 * @h: the 1st node pointer.
 * Return: size of list.
 */

size_t print_list(const list_t *h)
{
	size_t m = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		m++;
	}
	return (m);
}

/**
 * node_starts_with - the entry point.
 * Description - returns node whose string starts with prefix.
 * @node: the list head pointer.
 * @prefix: string to match.
 * @c: the next character after prefix to match.
 * Return: match node or null.
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *m = NULL;

	while (node)
	{
		m = starts_with(node->str, prefix);
		if (m && ((c == -1) || (*m == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - the entry point.
 * Description - gets the index of a node.
 * @head: the list head pointer.
 * @node: pointer to the node.
 * Return: index of node or -1.
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t m = 0;

	while (head)
	{
		if (head == node)
			return (m);
		head = head->next;
		m++;
	}
	return (-1);
}
