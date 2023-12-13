#include "main.h"

/**
 * free_data - The Entry Point.
 * Description - frees data structure.
 * @datash: the data structure.
 * Return: .
 */

void free_data(data_shell *datash)
{
	unsigned int m;

	for (m = 0; datash->_environ[m]; m++)
	{
		free(datash->_environ[m]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - The Entry Point.
 * Description - Initialize data structure.
 * @datash: the data structure.
 * @av: the argu vector.
 * Return: .
 */

void set_data(data_shell *datash, char **av)
{
	unsigned int m;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (m = 0; environ[m]; m++)
		;

	datash->_environ = malloc(sizeof(char *) * (m + 1));

	for (m = 0; environ[m]; m++)
	{
		datash->_environ[m] = _strdup(environ[m]);
	}

	datash->_environ[m] = NULL;
	datash->pid = aux_itoa(getpid());
}

/**
 * main - The Entry Point.
 * @ac: the argu count.
 * @av: the argu vector.
 * Return: Always 0 on success.
 */

int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datash, av);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
