#include "shell.h"

/**
 * _memset - the entry point.
 * Description - fills memory with a constant byte.
 * @s: the memory area pointer.
 * @b: the byte to fill *s with.
 * @n: the amount of bytes to be filled.
 * Return: (s) a pointer to the memory area s.
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int m;

	for (m = 0; m < n; m++)
		s[m] = b;
	return (s);
}

/**
 * ffree - the entry point.
 * Description - frees a string of strings.
 * @pp: string of strings.
 */

void ffree(char **pp)
{
	char **m = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(m);
}

/**
 * _realloc - the entry point.
 * Description - reallocates a block of memory.
 * @ptr: pointer to previous malloc'ated block.
 * @old_size: byte size of previous block.
 * @new_size: byte size of new block.
 * Return: pointer to the old block name.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *m;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	m = malloc(new_size);
	if (!m)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		m[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (m);
}
