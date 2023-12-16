#include "shell.h"

static sig_atomic_t i;
/**
 * initialize_interrupted - the entry point.
 * Description - function to initialize the 'interrupted' variable.
 */

void initialize_interrupted(void)
{
	i = 0;
}


/**
 * signal_handler - the entry point.
 * Description - function for SIGINT (Ctrl+C).
 * @signal_number: the signal number.
 */

void signal_handler(int signal_number __attribute__((unused)))
{
	i = 1;
	write(STDOUT_FILENO, "\n$ ", 3);  /* Print a new prompt after Ctrl+C */
}

/**
 * setup_signal_handler - the entry point.
 * Description - function that sets up the Ctrl+C signal
 * handler using the signal function.
 */

void setup_signal_handler(void)
{
	signal(SIGINT, signal_handler);
}
