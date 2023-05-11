#include "shell.h"

/**
 * shell_loop - main shell loop
 * @cmd_info: the command info struct
 * @cmd_args: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(cmd_info_t *cmd_info, char **cmd_args)
{
    ssize_t read_ret = 0;
    int builtin_ret = 0;

    while (read_ret != -1 && builtin_ret != -2)
    {
        clear_cmd_info(cmd_info);
        if (is_interactive(cmd_info))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        read_ret = read_input(cmd_info);
        if (read_ret != -1)
        {
            set_cmd_info(cmd_info, cmd_args);
            builtin_ret = find_builtin_cmd(cmd_info);
            if (builtin_ret == -1)
                execute_external_cmd(cmd_info);
        }
        else if (is_interactive(cmd_info))
            _putchar('\n');
        free_cmd_info(cmd_info, 0);
    }
    write_history(cmd_info);
    free_cmd_info(cmd_info, 1);
    if (!is_interactive(cmd_info) && cmd_info->status)
        exit(cmd_info->status);
    if (builtin_ret == -2)
    {
        if (cmd_info->err_num == -1)
            exit(cmd_info->status);
        exit(cmd_info->err_num);
    }
    return (builtin_ret);
}

/**
 * find_builtin_cmd - finds a builtin command
 * @cmd_info: the command info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin_cmd(cmd_info_t *cmd_info)
{
    int i, builtin_ret = -1;
    builtin_table_t builtintbl[] = {
        {"exit", my_exit},
        {"env", my_env},
        {"help", my_help},
        {"history", my_history},
        {"setenv", my_setenv},
        {"unsetenv", my_unsetenv},
        {"cd", my_cd},
        {"alias", my_alias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].name; i++)
        if (_strcmp(cmd_info->argv[0], builtintbl[i].name) == 0)
        {
            cmd_info->line_count++;
            builtin_ret = builtintbl[i].func(cmd_info);
            break;
        }
    return (builtin_ret);
}

/**
 * find_command - finds a command in the system path
 * @info: pointer to the parameter & return info struct
 *
 * This function searches for a command by iterating over each directory in the system path
 * and appending the command name to each directory path until the command is found.
 */
void find_command(info_t *info)
{
	char *full_path = NULL;
	int i, num_non_delim_args;

	info->full_command_path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	/* Count the number of non-delimiter arguments */
	for (i = 0, num_non_delim_args = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			num_non_delim_args++;
	if (!num_non_delim_args)
		return;

	full_path = search_path(info, get_env_var(info, "PATH="), info->argv[0]);
	if (full_path)
	{
		info->full_command_path = full_path;
		execute_command(info);
	}
	else
	{
		if ((is_interactive(info) || get_env_var(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			execute_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "Command not found\n");
		}
	}
}

/**
 * execute_command - forks a child process to execute the command
 * @info: pointer to the parameter & return info struct
 *
 * This function forks a child process to execute the command and waits for the child
 * process to finish. If the child process fails to execute the command, this function
 * will print an error message and set the status code accordingly.
 */
void execute_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->full_command_path, info->argv, get_environment(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
