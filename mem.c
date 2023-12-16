#include "shell.h"

/**
 * _memcpy - the entry point.
 * Description - Function that copies memory area from source to destination.
 * @dest: destination memory area.
 * @src: source memory area.
 * @n: number of bytes to copy.
 * Return: destination memory area (dest).
 */

void *_memcpy(void *dest, const void *src, size_t n)
{
	size_t m;

	char *td = (char *) dest;
	const char *ts = (const char *) src;

	for (m = 0; m < n; m++)
	{
		td[m] = ts[m];
	}
	return (dest);
}
