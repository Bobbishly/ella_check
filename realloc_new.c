#include "my_shell.h"

/**
 * my_memset - fill memory with a constant byte
 * @mem_ptr: pointer to the memory area
 * @byte: the byte to fill the memory with
 * @size: the amount of bytes to be filled
 *
 * Return: pointer to the memory area mem_ptr
 */
char *my_memset(char *mem_ptr, char byte, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		mem_ptr[i] = byte;
	return (mem_ptr);
}

/**
 * free_string_array - frees a string array
 * @str_array: string array to be freed
 */
void free_string_array(char **str_array)
{
	char **array_ptr = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(array_ptr);
}

/**
 * my_realloc - reallocates a block of memory
 * @mem_ptr: pointer to the previous block of memory
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the newly allocated memory block
 */
void *my_realloc(void *mem_ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_mem_ptr;

	if (!mem_ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(mem_ptr), NULL);
	if (new_size == old_size)
		return (mem_ptr);

	new_mem_ptr = malloc(new_size);
	if (!new_mem_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_mem_ptr[old_size] = ((char *)mem_ptr)[old_size];
	free(mem_ptr);
	return (new_mem_ptr);
}
