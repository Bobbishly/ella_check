#include "shell.h"

/**
 * my_free - releases a pointer and sets the address to NULL
 * @p: pointer to release
 *
 * Returns: 1 if successful, otherwise 0.
 */
int my_free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
