#include "shell.h"

/**
 * remove_comments - the entry point.
 * Decription - function that remove comments from a command before parsing.
 * @command: input command.
 * Return: the modified command if # are found
 * or the command itself if no comments are found.
 */

char *remove_comments(char *command)
{
	size_t o;
	const char *p;
	char *mc;

	/* Find the first occurrence of # */
	p = _strchr(command, '#');

	/* If no # is found, return the command */
	if (p == NULL)
		return (command);

	/* Calc. the offset, i.e., the position of the # character in the string */
	o = p - command;

	/* Check if # is at the start of the string or follows whitespace */
	if (o == 0 || (o > 0 && isspace(command[o - 1])))
	{
		/* Allocate a new string to store the modified command */
		mc = malloc(o + 1);
		if (mc == NULL)
		{
			fprintf(stderr, "Memory allocation error\n");
			safefree(mc);
			exit(EXIT_FAILURE);
		}

		/* Copy the relevant portion of the command into the new string */
		_strncpy(mc, command, o);
		mc[o] = '\0';

		return (mc);
	}
	else
	{
		/* If # is not at start or following whitespace, return the command */
		return (command);
	}
}
