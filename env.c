#include "shell.h"

/**
 * _getenv - the entry point.
 * Description - function that gets an environment variable.
 * @name: environment variable name.
 * Return: A pointer to the value in the environment,
 * or NULL if there is no match.
 */

char *_getenv(const char *name)
{
	int m = 0;
	size_t l = 0;
	char *tn = (char *)name;

	/* Check if the input name or the environment variable is NULL */
	if (name == NULL || environ == NULL)
		return (NULL);

	l = strlen(tn); /* let's get the length of the input name.*/

	while (environ != NULL)
	{
		/* Check if the current env. variable matches the input name. */
		if (_strncmp(environ[m], tn, l) == 0 && environ[m][l] == '=')
		{
			return (&(environ[m][l + 1]));
		}
		m++;
	}

	return (NULL);
}

/**
 * v_getenv - the entry point.
 * Description - function that gets the value of an environ var.
 * @name: environment variable.
 * Return: if the environment variable is found,
 * the function returns a pointer to its value.
 * If the environment variable is not found or if
 * the input is invalid, it returns NULL.
 */

char *v_getenv(const char *name)
{
	int m;
	char *ep;
	size_t nl;

	if (name == NULL || *name == '\0')
	{
		/* Invalid input, return NULL */
		return (NULL);
	}

	/* Iterate through the environment variables */
	for (m = 0; environ[m] != NULL; m++)
	{
		/* Find the position of the '=' char in the env. variable string */
		ep = _strchr(environ[m], '=');
		if (ep != NULL)
		{
			/* Calculate the length of the name */
			nl = ep - environ[m];

			/* Check if the current environment variable's name matches the input */
			if (_strncmp(environ[m], name, nl) == 0 &&
					nl == strlen(name))
			{
				/* Return the value part of the environment variable */
				return (ep + 1);
			}
		}
	}

	return (NULL);
}

/**
 * build_path_list - the entry point.
 * Description - function that builds a linked list from the
 * PATH environment variable.
 * @head: a double pointer to the head of the linked list.
 * Return: The head of the linked list.
 */

path_t *build_path_list(path_t **head)
{
	size_t m = 0;
	char *pe = NULL, **t = NULL;
	path_t *nn = NULL, *c = NULL;

	pe = _getenv("PATH");
	if (pe == NULL || *pe == '\0')
		return (NULL);

	t = _strtok(pe, ":");
	if (t == NULL)
		return (NULL);
	while (t[m] != NULL)
	{
		nn = malloc(sizeof(path_t));
		if (nn == NULL)
			return (NULL);

		nn->pathname = strdup(t[m]);
		if (nn->pathname == NULL)
		{
			safefree(nn);
			return (NULL);
		}
		nn->next = NULL;

		if (*head == NULL)
			(*head) = nn;
		else
		{
			c = *head;
			while (c->next != NULL)
				c = c->next;
			c->next = nn;
		}
		safefree(t[m]);
		m++;
	}
	free_string(&t); /* free tokens */
	return (*head);
}

/**
 * print_path_list - the entry point.
 * Description - function that prints the contents of the linked list.
 * @list: linked list head.
 */

void print_path_list(path_t *list)
{
	/* Check if the linked list is empty. */
	if (list == NULL)
		return;

	/* Iterate through the linked list and print each element. */
	while (list != NULL)
	{
		printf("%s\n", list->pathname);
		list = list->next;
	}
}


/**
 * free_path_list - the enrty point.
 * Description - function that frees the memory occupied by the linked list.
 * @list: A double pointer to the head of the linked list.
 */

void free_path_list(path_t **list)
{
	path_t *t;

	while (*list != NULL)
	{
		t = (*list);
		(*list) = (*list)->next;
		free(t->pathname);
		safefree(t);
	}
}
