#include "shell.h"

/**
 * _realloc - the entry point.
 * Description - function that reallocate dynamic memory.
 * @ptr: old memory block pointer.
 * @old_size: old memory block size.
 * @new_size: new memory block size.
 * Return: a pointer to the newly allocated memory,
 * otherwise NULL on failure.
 */

void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *nm;
	size_t cs;

	if (new_size == old_size)
	{
		return (ptr);
	}

	/* handle the free() equivalent call of the _realloc function */
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	nm = malloc(new_size);
	if (nm == NULL)
		return (NULL); /* memory allocation failed */

	if (ptr != NULL)
	{
		/* copy size based on minimum of old_size and new_size.*/
		cs = (old_size < new_size) ? old_size : new_size;

		/* copy content from old memory to new alloc'ed. memory */
		_memcpy(nm, ptr, cs);
		free(ptr);
	}
	return (nm);
}



