#include "main.h"

/**
 * add_sep_node_end - The Entry Point.
 * Description - adds a separator found at the end of a sep_list.
 * @head: the linked list head.
 * @sep: separator found (; | &).
 * Return: the address of the head.
 */

sep_list *add_sep_node_end(sep_list **head, char sep)
{
	sep_list *n, *t;

	n = malloc(sizeof(sep_list));
	if (n == NULL)
		return (NULL);

	n->separator = sep;
	n->next = NULL;
	t = *head;

	if (t == NULL)
	{
		*head = n;
	}
	else
	{
		while (t->next != NULL)
			t = t->next;
		t->next = n;
	}

	return (*head);
}

/**
 * free_sep_list - The Entry Point.
 * Description - frees a sep_list.
 * @head: the linked list head.
 * Return: .
 */

void free_sep_list(sep_list **head)
{
	sep_list *t;
	sep_list *c;

	if (head != NULL)
	{
		c = *head;
		while ((t = c) != NULL)
		{
			c = c->next;
			free(t);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - The Entry Point.
 * Description - adds a command line at the end of a line_list.
 * @head: the linked list head.
 * @line: the command line.
 * Return: the address of the head.
 */

line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *n, *t;

	n = malloc(sizeof(line_list));
	if (n == NULL)
		return (NULL);

	n->line = line;
	n->next = NULL;
	t = *head;

	if (t == NULL)
	{
		*head = n;
	}
	else
	{
		while (t->next != NULL)
			t = t->next;
		t->next = n;
	}

	return (*head);
}

/**
 * free_line_list - The Entry Point.
 * Description - frees a line_list.
 * @head: head of the linked list.
 * Return: .
 */

void free_line_list(line_list **head)
{
	line_list *t;
	line_list *c;

	if (head != NULL)
	{
		c = *head;
		while ((t = c) != NULL)
		{
			c = c->next;
			free(t);
		}
		*head = NULL;
	}
}
