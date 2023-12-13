#include "main.h"

/**
 * _memcpy - The Entry Point.
 * Description - copies information between void pointers.
 * @newptr: the destination pointer.
 * @ptr: the source pointer.
 * @size: new pointer size.
 * Return: .
 */

void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int m;

	for (m = 0; m < size; m++)
		char_newptr[m] = char_ptr[m];
}

/**
 * _realloc - The Entry Point.
 * Description - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *np;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	np = malloc(new_size);
	if (np == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(np, ptr, new_size);
	else
		_memcpy(np, ptr, old_size);

	free(ptr);
	return (np);
}

/**
 * _reallocdp - The Entry Point.
 * Description - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */

char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **np;
	unsigned int m;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	np = malloc(sizeof(char *) * new_size);
	if (np == NULL)
		return (NULL);

	for (m = 0; m < old_size; m++)
		np[m] = ptr[m];

	free(ptr);

	return (np);
}
