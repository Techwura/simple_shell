#include "shell.h"

/**
 * prompt - the entry point.
 * Description - function that displays the shell prompt.
 */

void prompt(void)
{
	if (isatty(STDIN_FILENO))
		printf("$ ");

	/* Flush the standard output to ensure prompt is displayed */
	fflush(stdout);
}


/**
 * handle_empty_prompt - the entry point.
 * Description - function that handles the case when the user
 * enters an empty prompt
 * @bytes_read: bytes read.
 * @lsh: relevant information.
 */

void handle_empty_prompt(ssize_t bytes_read, shell_t *lsh)
{
	/* user entered an empty prompt or CTRL+D was received? */
	if (bytes_read == -1)
	{
		/* Checking if the standard input is a terminal */
		if (isatty(STDIN_FILENO))
		{
			/* Print "exit" to the terminal */
			printf("exit\n");
		}
		exit_shell(lsh, free_up);
	}
}
