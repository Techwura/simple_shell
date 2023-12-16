#include "shell.h"

/**
 * execute_command - the entry point.
 * Description - function that executes a shell command using fork and execve.
 * @command: execute command.
 * @lsh: relevant information.
 * Return: Exit status of the executed command, otherwise -1 on failure.
 */

int execute_command(const char *command, shell_t *lsh)
{
	int s;
	pid_t p = fork();

	if (p == -1)
		handle_error("fork failed");

	if (p == 0)
	{
		if (execve(command, lsh->tokenized_commands, environ) == -1)
		{
			if (errno == EACCES)
			{
				fprintf(stderr, "%s: %lu: %s\n", lsh->prog_name, lsh->cmd_count,
				strerror(errno));
				return (127);
			}

			perror("execve");
			return (-1);
		}
	}
	else
	{
		if (waitpid(p, &s, 0) == -1)
		{
			perror("wait");
			return (-1);
		}
		if (WIFEXITED(s))
		{
			/* normal termination */
			return (WEXITSTATUS(s));
		}
	}

	return (0);
}
