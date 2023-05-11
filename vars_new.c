#include "my_shell.h"

/**
 * check_delimiter - test if current char in buffer is a delimiter
 * @args: the argument struct
 * @buffer: the char buffer
 * @index: address of current position in buffer
 *
 * Return: 1 if delimiter, 0 otherwise
 */
int check_delimiter(args_t *args, char *buffer, size_t *index)
{
    size_t j = *index;

    if (buffer[j] == '|' && buffer[j + 1] == '|')
    {
        buffer[j] = 0;
        j++;
        args->cmd_type = CMD_OR;
    }
    else if (buffer[j] == '&' && buffer[j + 1] == '&')
    {
        buffer[j] = 0;
        j++;
        args->cmd_type = CMD_AND;
    }
    else if (buffer[j] == ';') /* found end of this command */
    {
        buffer[j] = 0; /* replace semicolon with null */
        args->cmd_type = CMD_CHAIN;
    }
    else
        return (0);
    *index = j;
    return (1);
}

/**
 * check_cmd_type - checks if we should continue chaining based on last status
 * @args: the argument struct
 * @buffer: the char buffer
 * @index: address of current position in buffer
 * @start: starting position in buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_cmd_type(args_t *args, char *buffer, size_t *index, size_t start, size_t len)
{
    size_t j = *index;

    if (args->cmd_type == CMD_AND)
    {
        if (args->status)
        {
            buffer[start] = 0;
            j = len;
        }
    }
    if (args->cmd_type == CMD_OR)
    {
        if (!args->status)
        {
            buffer[start] = 0;
            j = len;
        }
    }

    *index = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @args: the argument struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(args_t *args)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = node_starts_with(args->alias_list, args->arguments[0], '=');
        if (!node)
            return (0);
        free(args->arguments[0]);
        p = _strchr(node->str, '=');
        if (!p)
            return (0);
        p = _strdup(p + 1);
        if (!p)
            return (0);
        args->arguments[0] = p;
    }
    return (1);
}

/**
 * updateVariables - Replaces variables in the tokenized command string.
 * @infoPtr: Pointer to the parameter struct.
 *
 * Returns: 1 if any variable is replaced, otherwise 0.
 */
int updateVariables(info_t *infoPtr)
{
    int i = 0;
    list_t *node;

    for (i = 0; infoPtr->command[i]; i++)
    {
        // Check if the tokenized command starts with '$' and contains more than one character.
        if (infoPtr->command[i][0] != '$' || !infoPtr->command[i][1])
            continue;

        // Check if the tokenized command is "$?".
        if (!_strcmp(infoPtr->command[i], "$?"))
        {
            // Replace the token with the exit status of the previous command.
            replaceString(&(infoPtr->command[i]),
                _strdup(convertNumber(infoPtr->exitStatus, 10, 0)));
            continue;
        }
        // Check if the tokenized command is "$$".
        if (!_strcmp(infoPtr->command[i], "$$"))
        {
            // Replace the token with the current process ID.
            replaceString(&(infoPtr->command[i]),
                _strdup(convertNumber(getProcessID(), 10, 0)));
            continue;
        }
        // Find the corresponding node in the environment list for the given variable.
        node = findNode(infoPtr->envList, &infoPtr->command[i][1], '=');
        if (node)
        {
            // Replace the token with the corresponding value from the environment list.
            replaceString(&(infoPtr->command[i]),
                _strdup(_strchr(node->string, '=') + 1));
            continue;
        }
        // Replace the token with an empty string if the variable is not found in the environment list.
        replaceString(&infoPtr->command[i], _strdup(""));

    }
    return (0);
}

/**
 * replaceString - Replaces a string.
 * @oldStr: Address of the old string.
 * @newStr: New string to replace with.
 *
 * Returns: 1 if the old string is replaced, otherwise 0.
 */
int replaceString(char **oldStr, char *newStr)
{
    // Free the memory used by the old string.
    free(*oldStr);
    // Assign the address of the new string to the old string.
    *oldStr = newStr;
    return (1);
}
