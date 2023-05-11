#include "my_shell.h"

/**
 * is_executable - determines if a file is an executable command
 * @shell_info: the shell info struct
 * @path: path to the file
 *
 * Returns: 1 if true, 0 otherwise
 */
int is_executable(shell_info_t *shell_info, char *path)
{
    struct stat file_stat;

    (void)shell_info;
    if (!path || stat(path, &file_stat))
        return (0);

    if (file_stat.st_mode & S_IFREG)
    {
        return (1);
    }
    return (0);
}

/**
 * duplicate_chars - duplicates characters
 * @path_string: the PATH string
 * @start_index: starting index
 * @stop_index: stopping index
 *
 * Returns: pointer to new buffer
 */
char *duplicate_chars(char *path_string, int start_index, int stop_index)
{
    static char buffer[1024];
    int i = 0, k = 0;

    for (k = 0, i = start_index; i < stop_index; i++)
        if (path_string[i] != ':')
            buffer[k++] = path_string[i];
    buffer[k] = 0;
    return (buffer);
}

/**
 * find_executable_path - finds the path to the executable file in the PATH string
 * @shell_info: the shell info struct
 * @path_string: the PATH string
 * @executable_name: the executable name to find
 *
 * Returns: full path of executable if found or NULL
 */
char *find_executable_path(shell_info_t *shell_info, char *path_string, char *executable_name)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!path_string)
        return (NULL);

    if ((_strlen(executable_name) > 2) && starts_with(executable_name, "./"))
    {
        if (is_executable(shell_info, executable_name))
            return (executable_name);
    }

    while (1)
    {
        if (!path_string[i] || path_string[i] == ':')
        {
            path = duplicate_chars(path_string, curr_pos, i);
            if (!*path)
                _strcat(path, executable_name);
            else
            {
                _strcat(path, "/");
                _strcat(path, executable_name);
            }
            if (is_executable(shell_info, path))
                return (path);
            if (!path_string[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return (NULL);
}
