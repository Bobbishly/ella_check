#include "shell.h"

/**
 * buffer_input - buffers chained commands
 * @shell_info: parameter struct
 * @buf_address: address of buffer
 * @len_address: address of len var
 *
 * Return: bytes read
 */
ssize_t buffer_input(shell_info_t *shell_info, char **buf_address, size_t *len_address)
{
	ssize_t num_bytes = 0;
	size_t len_p = 0;

	if (!*len_address) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)shell_info->command_buffer);*/
		free(*buf_address);
		*buf_address = NULL;
		signal(SIGINT, interrupt_handler);
#if USE_GETLINE
		num_bytes = getline(buf_address, &len_p, stdin);
#else
		num_bytes = get_line(shell_info, buf_address, &len_p);
#endif
		if (num_bytes > 0)
		{
			if ((*buf_address)[num_bytes - 1] == '\n')
			{
				(*buf_address)[num_bytes - 1] = '\0'; /* remove trailing newline */
				num_bytes--;
			}
			shell_info->linecount_flag = 1;
			remove_comments(*buf_address);
			build_history_list(shell_info, *buf_address, shell_info->histcount++);
			/* if (_strchr(*buf_address, ';')) is this a command chain? */
			{
				*len_address = num_bytes;
				shell_info->command_buffer = buf_address;
			}
		}
	}
	return (num_bytes);
}

/**
 * get_shell_input - gets a line minus the newline
 * @shell_info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_shell_input(shell_info_t *shell_info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t num_bytes = 0;
	char **buf_pointer = &(shell_info->arguments), *p;

	_putchar(BUF_FLUSH);
	num_bytes = buffer_input(shell_info, &buf, &len);
	if (num_bytes == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_command_chain(shell_info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_command_chain(shell_info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			shell_info->command_buffer_type = CMD_NORM;
		}

		*buf_pointer = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_pointer = buf; /* else not a chain, pass back buffer from get_line() */
	return (num_bytes); /* return length of buffer from get_line() */
}

/**
 * read_buffer - reads a buffer from a file descriptor
 * @info: information about the file descriptor
 * @buffer: buffer to read into
 * @buffer_size: maximum size of the buffer
 *
 * Return: the number of bytes read, or -1 on failure
 */
ssize_t read_buffer(FileInfo *info, char *buffer, size_t *buffer_size)
{
	ssize_t bytes_read = 0;

	if (*buffer_size)
		return (0);
	bytes_read = read(info->fd, buffer, BUFFER_SIZE);
	if (bytes_read >= 0)
		*buffer_size = bytes_read;
	return (bytes_read);
}

/**
 * get_line - reads a line from a file descriptor
 * @info: information about the file descriptor
 * @buffer_ptr: pointer to buffer for storing the line
 * @buffer_size: size of the buffer pointed to by buffer_ptr
 *
 * Return: the number of bytes read, or -1 on failure
 */
int get_line(FileInfo *info, char **buffer_ptr, size_t *buffer_size)
{
	static char buffer[BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytes_read = 0, bytes_stored = 0;
	char *buffer = NULL, *new_buffer = NULL, *c;

	buffer = *buffer_ptr;
	if (buffer && buffer_size)
		bytes_stored = *buffer_size;
	if (i == len)
		i = len = 0;

	bytes_read = read_buffer(info, buffer, &len);
	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_buffer = _realloc(buffer, bytes_stored, bytes_stored ? bytes_stored + k : k + 1);
	if (!new_buffer) /* MALLOC FAILURE! */
		return (buffer ? free(buffer), -1 : -1);

	if (bytes_stored)
		_strncat(new_buffer, buffer + i, k - i);
	else
		_strncpy(new_buffer, buffer + i, k - i + 1);

	bytes_stored += k - i;
	i = k;
	buffer = new_buffer;

	if (buffer_size)
		*buffer_size = bytes_stored;
	*buffer_ptr = buffer;
	return (bytes_stored);
}

/**
 * sigint_handler - handles SIGINT signal (Ctrl+C) by printing prompt
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigint_handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_OUTPUT);
}
