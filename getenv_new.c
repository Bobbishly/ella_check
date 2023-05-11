#include "shell.h"

/**
 * copy_str_array - returns a copy of a string array
 * @info: structure containing potential arguments
 * Return: copy of the string array
 */
char **copy_str_array(info_t *info)
{
	if (!info->str_array || info->array_changed)
	{
		info->str_array = list_to_str_array(info->str_list);
		info->array_changed = 0;
	}

	return (info->str_array);
}

/**
 * unset_env_var - Remove an environment variable
 * @info: structure containing potential arguments
 * @var: the string env var property
 *  Return: 1 on delete, 0 otherwise
 */
int unset_env_var(info_t *info, char *var)
{
	list_t *node = info->str_list;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->array_changed = delete_node_at_index(&(info->str_list), i);
			i = 0;
			node = info->str_list;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->array_changed);
}

/**
 * set_env_var - Initialize a new environment variable, or modify an existing one
 * @info: structure containing potential arguments
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int set_env_var(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->str_list;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = b=uf;
			info->array_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->str_list), buf, 0);
	free(buf);
	info->array_changed = 1;
	return (0);
}
