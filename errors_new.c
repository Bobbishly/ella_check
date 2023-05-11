#include "shell.h"

/**
 * print_string - prints a string to standard error output
 * @str: pointer to the string to be printed
 *
 * This function prints a given string to standard error output. If the string
 * pointer is NULL, then this function returns immediately without printing
 * anything.
 */
void print_string(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		write_stderr(str[i]);
		i++;
	}
}

/**
 * write_stderr - writes a character to standard error output
 * @c: the character to be written
 *
 * This function writes a given character to standard error output. If the
 * character is the FLUSH constant or the write buffer is full, then the
 * contents of the buffer are written to standard error output and the buffer
 * is reset. Otherwise, the character is added to the buffer.
 *
 * Return: On success, 1. On failure, -1 is returned and errno is set
 *         appropriately.
 */
int write_stderr(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(STDERR_FILENO, buf, i);
		i = 0;
	}

	if (c != FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * write_to_fd - writes a character to a file descriptor
 * @c: the character to be written
 * @fd: the file descriptor to write to
 *
 * This function writes a given character to a file descriptor. If the
 * character is the FLUSH constant or the write buffer is full, then the
 * contents of the buffer are written to the file descriptor and the buffer
 * is reset. Otherwise, the character is added to the buffer.
 *
 * Return: On success, 1. On failure, -1 is returned and errno is set
 *         appropriately.
 */
int write_to_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * print_string_to_fd - prints a string to a file descriptor
 * @str: pointer to the string to be printed
 * @fd: the file descriptor to write to
 *
 * This function prints a given string to a file descriptor. If the string
 * pointer is NULL, then this function returns immediately without printing
 * anything. Otherwise, the function calls the write_to_fd() function to
 * write each character in the string to the file descriptor.
 *
 * Return: The number of characters written to the file descriptor.
 */
int print_string_to_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
	{
		i += write_to_fd(*str++, fd);
	}

	return (i);
}
