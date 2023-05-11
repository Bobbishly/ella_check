#include "shell.h"

/**
 * string_to_int - converts a string to an integer
 * @str: the string to be converted
 *
 * Return: converted number, or -1 on error
 */
int string_to_int(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');

			if (result > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}

	return (result);
}

/**
 * print_error_msg - prints an error message to standard error
 * @info: pointer to parameter & return info struct
 * @error_type: string containing specified error type
 *
 * Return: nothing
 */
void print_error_msg(info_t *info, char *error_type)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_type);
}

/**
 * print_decimal - prints a decimal (integer) number (base 10)
 * @num: the input number
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int num, int fd)
{
	int (*put_func)(char) = _putchar;
	int i, count = 0;
	unsigned int abs_val, current;

	if (fd == STDERR_FILENO)
	{
		put_func = _eputchar;
	}

	if (num < 0)
	{
		abs_val = -num;
		put_func('-');
		count++;
	}
	else
	{
		abs_val = num;
	}

	current = abs_val;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_val / i)
		{
			put_func('0' + current / i);
			count++;
		}
		current %= i;
	}

	put_func('0' + current);
	count++;

	return (count);
}

/**
 * convert_num_to_str - converter function for numbers
 * @num: the number to convert
 * @base: the base to convert the number to
 * @flags: flags for the argument
 *
 * Return: string representation of the number
 */
char *convert_num_to_str(long int num, int base, int flags)
{
	static char *char_array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long abs_val = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		abs_val = -num;
		sign = '-';
	}

	char_array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = char_array[abs_val % base];
		abs_val /= base;
	} while (abs_val != 0);

	if (sign)
	{
		*--ptr = sign;
	}

	return (ptr);
}

/**
 * remove_comments - Replaces first instance of '#' with '\0'
 * @line: Address of the string to modify
 *
 * Return: Nothing
 */
void remove_comments(char *line)
{
	int i;

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == '#' && (i == 0 || line[i - 1] == ' '))
		{
			line[i] = '\0';
			break;
		}
	}
}

