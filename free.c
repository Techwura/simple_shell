#include "shell.h"

/**
 * _free - the entry point.
 * Description - function that frees/deallocates a pointer/dynamically
 * allocated memory and sets it to NULL.
 * @ptr: pointer to be freed.
 */

void _free(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
