#include "shell.h"

/**
 * execute_with_path - the entry point.
 * Description - function that search for and execute a command
 * using the PATH variable.
 * @lsh: relevant information.
 * Return: always 0 on success, otherwise -1 on failure.
 */
int execute_with_path(shell_t *lsh)
{
	char p[BUFFER_SIZE];
	path_t *pl = lsh->path_list;

	/* Iterate through the linked list of directories in the PATH.*/
	while (pl != NULL)
	{
		/**
		 *  Construct the full path by concatenating the directory, "/",
		 *  and the command.
		 */
		snprintf(p, sizeof(p), "%.*s/%s", (int)(sizeof(p) -
		strlen(lsh->tokenized_commands[0]) - 2), pl->pathname,
		lsh->tokenized_commands[0]);
		/* printf("Executing: %s\n", path); */


		/* Check if the constructed path is executable. */
		if (access(p, X_OK) == 0)
		{
			/* Execute the command and return the result. */
			return (execute_command(p, lsh));
		}
		/* Check if the command is executable in the current directory.*/
		else if (access(lsh->tokenized_commands[0], X_OK) == 0)
		{
			/* Execute the command and return the result.*/
			return (execute_command(lsh->tokenized_commands[0], lsh));
		}

		/* Move to the next directory in the PATH. */
		pl = pl->next;
	}

	return (-1);
}

/**
 * execute_file_as_input - the entry point.
 * Description - function that execute commands from a file in a shell.
 * @filename: The name of the file containing commands.
 * @lsh: shell structure pointer.
 */

void execute_file_as_input(char *filename, shell_t *lsh)
{
	ssize_t br;
	int m;
	size_t l;

	m = open(filename, O_RDONLY);
	if (m == -1)
	{
		free_path_list(&lsh->path_list);
		fprintf(stderr, "%s: 0: Can't open %s\n", lsh->prog_name, filename);
		exit(EXIT_FAILURE);
	}

	br = _getline(&lsh->user_input, &l, m);

	if (close(m) == -1)
		fprintf(stderr, "Error: unable to close file descriptor #%d\n", m);

	if (br == -1)
	{
		lsh->exit_code = -1;
		exit_shell(lsh, free_up);
	}

	if (br)
	{
		lsh->prog_name = filename;
		parse_input(lsh);
	}

	exit_shell(lsh, free_up);
}
