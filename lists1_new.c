#include "new_shell.h"

/**
 * get_list_size - returns the size of a linked list
 * @head: pointer to the head of the linked list
 *
 * Return: the size of the linked list
 */
size_t get_list_size(const list_t *head)
{
	size_t size = 0;

	while (head)
	{
		head = head->next;
		size++;
	}
	return (size);
}

/**
 * list_to_array - returns an array of strings from the list_t structure
 * @head: pointer to the head of the linked list
 *
 * Return: an array of strings
 */
char **list_to_array(list_t *head)
{
	list_t *node = head;
	size_t size = get_list_size(head), i, j;
	char **str_array;
	char *str;

	if (!head || !size)
		return (NULL);
	str_array = malloc(sizeof(char *) * (size + 1));
	if (!str_array)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(get_string_length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}

		str = copy_string(str, node->str);
		str_array[i] = str;
	}
	str_array[i] = NULL;
	return (str_array);
}

/**
 * print_linked_list - prints all elements of a linked list
 * @head: pointer to the head of the linked list
 *
 * Return: the size of the linked list
 */
size_t print_linked_list(const list_t *head)
{
	size_t size = 0;

	while (head)
	{
		print_number(convert_number(head->num, 10, 0));
		print_character(':');
		print_character(' ');
		print_string(head->str ? head->str : "(nil)");
		print_string("\n");
		head = head->next;
		size++;
	}
	return (size);
}

/**
 * find_node_by_prefix - finds the node whose string starts with the given prefix
 * @head: pointer to the head of the linked list
 * @prefix: the prefix to search for
 * @next_char: the next character to match after the prefix, or -1 if not specified
 *
 * Return: the node whose string starts with the given prefix, or NULL if not found
 */
list_t *find_node_by_prefix(list_t *head, char *prefix, char next_char)
{
	char *p = NULL;

	while (head)
	{
		p = find_prefix(head->str, prefix);
		if (p && ((next_char == -1) || (*p == next_char)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to the head of the linked list
 * @node: pointer to the node
 *
 * Return: the index of the node, or -1 if not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
