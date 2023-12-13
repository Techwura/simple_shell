#include "main.h"

/**
 * bring_line - The Entry Point.
 * Description - assigns the line var for get_line.
 * @lineptr: buffer that store the input string.
 * @buffer: string that is been called to line.
 * @n: the size of line.
 * @j: the size of buffer.
 */

void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - The Entry Point.
 * Description - Read inpt from stream.
 * @lineptr: buffer that stores the input.
 * @n: size of lineptr.
 * @stream: the read stream.
 * Return: number of bytes.
 */

ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int m;
	static ssize_t input;
	ssize_t r;
	char *b;
	char h = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	b = malloc(sizeof(char) * BUFSIZE);
	if (b == 0)
		return (-1);
	while (h != '\n')
	{
		m = read(STDIN_FILENO, &h, 1);
		if (m == -1 || (m == 0 && input == 0))
		{
			free(b);
			return (-1);
		}
		if (m == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			b = _realloc(b, input, input + 1);
		b[input] = h;
		input++;
	}
	b[input] = '\0';
	bring_line(lineptr, n, b, input);
	r = input;
	if (m != 0)
		input = 0;
	return (r);
}
