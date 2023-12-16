#include "shell.h"

/**
 * _getline - the entry Point.
 * Description - function for reading input from a file descriptor.
 * @lineptr: buffer storing the input line.
 * @n: size of the buffer.
 * @fd: file descriptor.
 * Return: number of bytes read, otherwise -1 on failure.
 */

ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	ssize_t br = 0;
	size_t p = 0, ns;
	char str;
	char *buf;

	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr == NULL || *n == 0)
	{
		*lineptr = (char *)malloc(BUFFER_SIZE);
		if (*lineptr == NULL)
			return (-1);
		*n = BUFFER_SIZE;
	}
	while (read(fd, &str, 1) > 0)
	{
		if (p >= *n - 1)
		{
			ns = *n * 2;
			buf = (char *)realloc(*lineptr, ns);
			if (buf == NULL)
				return (-1);
			*lineptr = buf;
			*n = ns;
		}
		(*lineptr)[p++] = str;
		br++;

		if (str == '\n')
			break;
	}

	if (br == 0)
		return (-1);

	(*lineptr)[p] = '\0';
	return (br);
}
