#include "shell.h"

/**
 * init_info - initializes info_t struct
 * @info: struct address
 */
void init_info(info_t *info)
{
	info->arg_str = NULL;
	info->arg_arr = NULL;
	info->path_str = NULL;
	info->arg_count = 0;
}

/**
 * fill_info - fills info_t struct
 * @info: struct address
 * @av: argument vector
 */
void fill_info(info_t *info, char **av)
{
	int i = 0;

	info->program_name = av[0];
	if (info->arg_str)
	{
		info->arg_arr = strtow(info->arg_str, " \t");
		if (!info->arg_arr)
		{

			info->arg_arr = malloc(sizeof(char *) * 2);
			if (info->arg_arr)
			{
				info->arg_arr[0] = _strdup(info->arg_str);
				info->arg_arr[1] = NULL;
			}
		}
		for (i = 0; info->arg_arr && info->arg_arr[i]; i++)
			;
		info->arg_count = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	ffree(info->arg_arr);
	info->arg_arr = NULL;
	info->path_str = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg_str);
		if (info->env_list)
			free_list(&(info->env_list));
		if (info->history_list)
			free_list(&(info->history_list));
		if (info->alias_list)
			free_list(&(info->alias_list));
		ffree(info->environ_arr);
			info->environ_arr = NULL;
		bfree((void **)info->cmd_buf);
		if (info->read_fd > 2)
			close(info->read_fd);
		_putchar(BUF_FLUSH);
	}
}
