#include "custom_shell.h"

/**
 * custom_exit - exits the shell
 * @cmd_info: Pointer to a structure containing potential arguments.
 *             Used to maintain constant function prototype.
 *
 * Return: exits with a given exit status (0) if cmd_info->args[0] != "exit"
 */
int custom_exit(cmd_info_t *cmd_info)
{
	int exit_status;

	if (cmd_info->args[1]) /* If there is an exit argument */
	{
		exit_status = custom_atoi(cmd_info->args[1]);
		if (exit_status == -1)
		{
			cmd_info->status = 2;
			print_custom_error(cmd_info, "Illegal number: ");
			_print_custom_str(cmd_info->args[1]);
			_putchar('\n');
			return (1);
		}
		cmd_info->exit_status = custom_atoi(cmd_info->args[1]);
		return (-2);
	}
	cmd_info->exit_status = -1;
	return (-2);
}

/**
 * custom_cd - changes the current directory of the process
 * @cmd_info: Pointer to a structure containing potential arguments.
 *            Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int custom_cd(cmd_info_t *cmd_info)
{
	char *cwd, *dir, buffer[1024];
	int chdir_ret;

	cwd = custom_getcwd(buffer, 1024);
	if (!cwd)
		_print_custom_str("TODO: >>getcwd failure emsg here<<\n");
	if (!cmd_info->args[1])
	{
		dir = custom_getenv(cmd_info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = custom_getenv(cmd_info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (custom_strcmp(cmd_info->args[1], "-") == 0)
	{
		if (!custom_getenv(cmd_info, "OLDPWD="))
		{
			_print_custom_str(cwd);
			_putchar('\n');
			return (1);
		}
		_print_custom_str(custom_getenv(cmd_info, "OLDPWD="));
		_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = custom_getenv(cmd_info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(cmd_info->args[1]);
	if (chdir_ret == -1)
	{
		print_custom_error(cmd_info, "can't cd to ");
		_print_custom_str(cmd_info->args[1]);
		_putchar('\n');
	}
	else
	{
		custom_setenv(cmd_info, "OLDPWD", custom_getenv(cmd_info, "PWD="));
		custom_setenv(cmd_info, "PWD", custom_getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * custom_help - prints a help message
 * @cmd_info: Pointer to a structure containing potential arguments.
 *            Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int custom_help(cmd_info_t *cmd_info)
{
	char **arg_array;

	arg_array = cmd_info->args;
	_print_custom_str("help call works. Function not yet implemented \n");
	if (0)
		_print_custom_str(*arg_array); /* temp att_unused workaround */
	return (0);
}
