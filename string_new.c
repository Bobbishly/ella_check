#include "my_shell.h"

/**
 * my_strlen - calculates the length of a string
 * @str: the string whose length to calculate
 *
 * Return: integer length of the string
 */
int my_strlen(char *str)
{
    int len = 0;

    if (!str)
        return 0;

    while (*str++)
        len++;

    return len;
}

/**
 * my_strcmp - compares two strings lexicographically
 * @str1: the first string to compare
 * @str2: the second string to compare
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int my_strcmp(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);
        str1++;
        str2++;
    }

    if (*str1 == *str2)
        return 0;
    else
        return (*str1 < *str2 ? -1 : 1);
}

/**
 * my_starts_with - checks if a string starts with another string
 * @str: the string to search
 * @prefix: the prefix to find
 *
 * Return: address of the next character of the string if found, NULL otherwise
 */
char *my_starts_with(const char *str, const char *prefix)
{
    while (*prefix)
    {
        if (*prefix++ != *str++)
            return NULL;
    }

    return (char *)str;
}

/**
 * my_strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *my_strcat(char *dest, char *src)
{
    char *result = dest;

    while (*dest)
        dest++;

    while (*src)
        *dest++ = *src++;

    *dest = *src;

    return result;
}
