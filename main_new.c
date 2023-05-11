#include "shell.h"

/**
 * entry_point - This is the entry point of the program.
 * @arg_count: The number of arguments passed to the program.
 * @arg_vector: An array of strings representing the arguments passed to the program.
 *
 * This function initializes some variables, opens a file, populates an environment list,
 * reads a history, and calls the main shell function before returning a status code indicating success or failure.
 *
 * Return: 0 if successful, 1 if an error occurred.
 */
int entry_point(int arg_count, char **arg_vector)
{
	info_t info[] = { INFO_INIT };
	int file_descriptor = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_descriptor)
		: "r" (file_descriptor));

	if (arg_count == 2)
	{
		file_descriptor = open(arg_vector[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(arg_vector[0]);
				_eputs(": 0: Can't open ");
				_eputs(arg_vector[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_fd = file_descriptor;
	}
	populate_env_list(info);
	read_history(info);
	run_shell(info, arg_vector);
	return (EXIT_SUCCESS);
}
