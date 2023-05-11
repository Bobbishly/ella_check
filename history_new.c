#include "shell.h"

/**
 * get_shell_history_file - obtains the file path of the shell history
 * @shell_info: pointer to the shell_info_t struct
 *
 * Return: pointer to allocated string containing shell history file path,
 *         NULL on failure
 */
char *get_shell_history_file(shell_info_t *shell_info)
{
	char *directory, *history_file_path;

	directory = get_env_var(shell_info, "HOME=");
	if (!directory)
		return (NULL);

	history_file_path = malloc(sizeof(char) * (strlen(directory) + strlen(SHELL_HISTORY_FILE) + 2));
	if (!history_file_path)
		return (NULL);

	history_file_path[0] = 0;
	strcpy(history_file_path, directory);
	strcat(history_file_path, "/");
	strcat(history_file_path, SHELL_HISTORY_FILE);

	return (history_file_path);
}

/**
 * write_shell_history - writes shell history to file
 * @shell_info: pointer to the shell_info_t struct
 *
 * Return: 1 on success, -1 on failure
 */
int write_shell_history(shell_info_t *shell_info)
{
	ssize_t file_descriptor;
	char *file_path = get_shell_history_file(shell_info);
	list_t *current_node = NULL;

	if (!file_path)
		return (-1);

	file_descriptor = open(file_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_path);

	if (file_descriptor == -1)
		return (-1);

	for (current_node = shell_info->history; current_node; current_node = current_node->next)
	{
		write_to_fd(current_node->str, file_descriptor);
		put_to_fd('\n', file_descriptor);
	}

	put_to_fd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);

	return (1);
}

/**
 * read_shell_history - reads shell history from file
 * @shell_info: pointer to the shell_info_t struct
 *
 * Return: number of shell history items read, 0 on failure
 */
int read_shell_history(shell_info_t *shell_info)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stat;
	char *file_contents = NULL, *file_path = get_shell_history_file(shell_info);

	if (!file_path)
		return (0);

	file_descriptor = open(file_path, O_RDONLY);
	free(file_path);

	if (file_descriptor == -1)
		return (0);

	if (!fstat(file_descriptor, &file_stat))
		file_size = file_stat.st_size;

	if (file_size < 2)
		return (0);

	file_contents = malloc(sizeof(char) * (file_size + 1));
	if (!file_contents)
		return (0);

	read_length = read(file_descriptor, file_contents, file_size);
	file_contents[file_size] = 0;

	if (read_length <= 0)
		return (free(file_contents), 0);

	close(file_descriptor);

	for (i = 0; i < file_size; i++)
		if (file_contents[i] == '\n')
		{
			file_contents[i] = 0;
			add_shell_history_item(shell_info, file_contents + last, line_count++);
			last = i + 1;
		}

	if (last != i)
		add_shell_history_item(shell_info, file_contents + last, line_count++);

	free(file_contents);
	shell_info->history_count = line_count;

	while (shell_info->history_count-- >= SHELL_HISTORY_MAX_ITEMS)
		delete_node_at_index(&(shell_info->history), 0);

	renumber_shell_history(shell_info);

	return (shell_info->history_count);
}

/**
 * add_history_entry - adds a new entry to a linked list of command history
 * @list: pointer to the head of the command history linked list
 * @command: the command to be added to the history
 * @index: the index of the new command in the history
 *
 * Return: Always 0
 */
int add_history_entry(history_list_t *list, char *command, int index)
{
	history_node_t *node = NULL;

	if (list->head)
		node = list->head;
	add_node_end(&node, command, index);

	if (!list->head)
		list->head = node;
	return (0);
}

/**
 * update_history_indices - renumbers the history list after changes
 * @list: pointer to the head of the command history linked list
 *
 * Return: the new total number of commands in the history
 */
int update_history_indices(history_list_t *list)
{
	history_node_t *node = list->head;
	int count = 0;

	while (node)
	{
		node->index = count++;
		node = node->next;
	}
	return (list->count = count);
}
