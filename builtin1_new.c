#include "my_shell.h"

/**
 * display_history - displays the command history list with line numbers
 * @my_info: Structure containing potential arguments
 * 
 * Return: Always 0
 */
int display_history(my_shell_info_t *my_info)
{
	print_linked_list(my_info->history_list);
	return (0);
}

/**
 * remove_alias - removes alias
 * @my_info: parameter struct
 * @alias_str: the alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(my_shell_info_t *my_info, char *alias_str)
{
	char *p, c;
	int ret;

	p = _strchr(alias_str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(my_info->alias_list),
		get_node_index(my_info->alias_list, node_starts_with(my_info->alias_list, alias_str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @my_info: parameter struct
 * @alias_str: the alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(my_shell_info_t *my_info, char *alias_str)
{
	char *p;

	p = _strchr(alias_str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remove_alias(my_info, alias_str));

	remove_alias(my_info, alias_str);
	return (add_node_end(&(my_info->alias_list), alias_str, 0) == NULL);
}

/**
 * print_alias_str - prints an alias string
 * @alias_node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias_str(linked_list_t *alias_node)
{
	char *p = NULL, *a = NULL;

	if (alias_node)
	{
		p = _strchr(alias_node->str, '=');
		for (a = alias_node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_handler - handles the 'alias' command
 * @my_info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int alias_handler(my_shell_info_t *my_info)
{
	int i = 0;
	char *p = NULL;
	linked_list_t *alias_node = NULL;

	if (my_info->argc == 1)
	{
		alias_node = my_info->alias_list;
		while (alias_node)
		{
			print_alias_str(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}

	for (i = 1; my_info->argv[i]; i++)
	{
		p = _strchr(my_info->argv[i], '=');
		if (p)
			set_alias(my_info, my_info->argv[i]);
		else
			print_alias_str(node_starts_with(my_info->alias_list, my_info->argv[i], '='));
	}

	return (0);
}
