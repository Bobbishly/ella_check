#include "my_shell.h"

/**
 * my_strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *my_strcpy(char *dest, char *src)
{
    int index = 0;

    if (dest == src || src == 0)
        return (dest);

    while (src[index])
    {
        dest[index] = src[index];
        index++;
    }
    dest[index] = 0;
    return (dest);
}

/**
 * my_strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *my_strdup(const char *str)
{
    int length = 0;
    char *ret;

    if (str == NULL)
        return (NULL);

    while (*str++)
        length++;

    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return (NULL);

    for (length++; length--;)
        ret[length] = *--str;

    return (ret);
}

/**
 * my_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void my_puts(char *str)
{
    int index = 0;

    if (!str)
        return;

    while (str[index] != '\0')
    {
        my_putchar(str[index]);
        index++;
    }
}

/**
 * my_putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return (1);
}
