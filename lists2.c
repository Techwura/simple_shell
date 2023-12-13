#include "main.h"

/**
 * add_rvar_node - The Entry Point.
 * Description - adds a variable at the end of a r_var list.
 * @head: the linked list head.
 * @lvar: variable length.
 * @val: variable value.
 * @lval: length of the value.
 * Return: address of the head.
 */

r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *n, *t;

	n = malloc(sizeof(r_var));
	if (n == NULL)
		return (NULL);

	n->len_var = lvar;
	n->val = val;
	n->len_val = lval;

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
 * free_rvar_list - The Entry Point.
 * Description - frees a r_var list.
 * @head: the linked list head.
 * Return: .
 */

void free_rvar_list(r_var **head)
{
	r_var *t;
	r_var *c;

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
