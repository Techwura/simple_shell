#include "shell.h"

/**
 * handle_error - the entry point.
 * Description - function that prints an error message using
 * perror and exit with failure status.
 * @message: The error message to be printed.
 */

void handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
