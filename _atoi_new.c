#include "shell.h"

/**
 * is_interactive_mode - determines whether shell is running in interactive mode
 * @info: pointer to the info_t struct
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - determines whether a character is a delimiter
 * @c: the character to check
 * @delimiter: pointer to the delimiter string
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_delimiter(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - determines whether a character is alphabetic
 * @c: the character to check
 *
 * Return: 1 if the character is alphabetic, 0 otherwise
 */
int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * string_to_integer - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if the string does not contain any numbers, the converted number otherwise
 */
int string_to_integer(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
