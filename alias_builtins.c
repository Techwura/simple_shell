#include "shell.h"

/**
 * shellby_alias - The Entry Point.
 * Description - Builtin command that either prints aliases.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * Return: Success on 0 otherwise -1 on error.
 */

int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int m, r = 0;
	char *v;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (r);
	}
	for (m = 0; args[m]; m++)
	{
		temp = aliases;
		v = _strchr(args[m], '=');
		if (!v)
		{
			while (temp)
			{
				if (_strcmp(args[m], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				r = create_error(args + m, 1);
		}
		else
			set_alias(args[m], v);
	}
	return (r);
}

/**
 * set_alias - The Entry Point.
 * Description - sets an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @var_name: the alias name.
 * @value: the alias value. First character is a '='.
 */

void set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int l, m, k;
	char *nv;

	*value = '\0';
	value++;
	l = _strlen(value) - _strspn(value, "'\"");
	nv = malloc(sizeof(char) * (l + 1));
	if (!nv)
		return;
	for (m = 0, k = 0; value[m]; m++)
	{
		if (value[m] != '\'' && value[m] != '"')
			nv[k++] = value[m];
	}
	nv[k] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = nv;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, nv);
}

/**
 * print_alias - The Entry Point.
 * Description - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */

void print_alias(alias_t *alias)
{
	char *as;
	int l = _strlen(alias->name) + _strlen(alias->value) + 4;

	as = malloc(sizeof(char) * (l + 1));
	if (!as)
		return;
	_strcpy(as, alias->name);
	_strcat(as, "='");
	_strcat(as, alias->value);
	_strcat(as, "'\n");

	write(STDOUT_FILENO, as, l);
	free(as);
}
/**
 * replace_aliases - The Entry Point.
 * Description - Goes through the arguments and replace any matching alias
 * with their value.
 * @args: 2D pointer to the args.
 * Return: 2D pointer to the args.
 */

char **replace_aliases(char **args)
{
	alias_t *temp;
	int m;
	char *nv;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (m = 0; args[m]; m++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[i], temp->name) == 0)
			{
				nv = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!nv)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(nv, temp->value);
				free(args[m]);
				args[m] = nv;
				m--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
