#include "my_shell.h"

/**
 * add_new_node - adds a new node to the beginning of the list
 * @list_head: address of pointer to head node
 * @string_val: str field of node
 * @node_index: node index used by history
 *
 * Return: size of list
 */
list_t *add_new_node(list_t **list_head, const char *string_val, int node_index)
{
	list_t *new_head_node;

	if (!list_head)
		return (NULL);
	new_head_node = malloc(sizeof(list_t));
	if (!new_head_node)
		return (NULL);
	_initialize_memory((void *)new_head_node, 0, sizeof(list_t));
	new_head_node->node_index = node_index;
	if (string_val)
	{
		new_head_node->string_val = _duplicate_string(string_val);
		if (!new_head_node->string_val)
		{
			free(new_head_node);
			return (NULL);
		}
	}
	new_head_node->next = *list_head;
	*list_head = new_head_node;
	return (new_head_node);
}

/**
 * add_new_node_end - adds a new node to the end of the list
 * @list_head: address of pointer to head node
 * @string_val: str field of node
 * @node_index: node index used by history
 *
 * Return: size of list
 */
list_t *add_new_node_end(list_t **list_head, const char *string_val, int node_index)
{
	list_t *new_node, *node;

	if (!list_head)
		return (NULL);

	node = *list_head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_initialize_memory((void *)new_node, 0, sizeof(list_t));
	new_node->node_index = node_index;
	if (string_val)
	{
		new_node->string_val = _duplicate_string(string_val);
		if (!new_node->string_val)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*list_head = new_node;
	return (new_node);
}

/**
 * print_only_strings - prints only the string_val element of a list_t linked list
 * @list_head_ptr: pointer to first node
 *
 * Return: size of list
 */
size_t print_only_strings(const list_t *list_head_ptr)
{
	size_t i = 0;

	while (list_head_ptr)
	{
		_put_string(list_head_ptr->string_val ? list_head_ptr->string_val : "(nil)");
		_put_string("\n");
		list_head_ptr = list_head_ptr->next;
		i++;
	}
	return (i);
}


/**
 * delete_node_at_pos - deletes node at given position
 * @head: address of pointer to first node
 * @pos: position of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_pos(list_t **head, unsigned int pos)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!pos)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == pos)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}


/**
 * destroy_list - deallocates all nodes in the list
 * @head_ptr: pointer to the pointer of the head node
 *
 * Return: void
 */
void destroy_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->name);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
