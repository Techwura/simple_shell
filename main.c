#include "shell.h"

/**
 * main - The Entry Point.
 * @ac: The arg count.
 * @av: The arg vector.
 * Return: Always 0 on success,otherwise 1 on error.
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int m = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (m)
			: "r" (m));
	if (ac == 2)
	{
		m = open(av[1], O_RDONLY);
		if (m == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = m;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
