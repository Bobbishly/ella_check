#include "shell.h"

/**
 * split_string - splits a string into an array of strings based on a delimiter
 * @str: the input string
 * @delimiter: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string(char *str, char *delimiter)
{
	int i, j, k, m, num_tokens = 0;
	char **tokens;

	if (str == NULL || str[0] == 0)
		return (NULL);

	if (!delimiter)
		delimiter = " ";

	/* Count the number of tokens in the string */
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimiter(str[i], delimiter) &&
		    (is_delimiter(str[i + 1], delimiter) || !str[i + 1]))
			num_tokens++;

	if (num_tokens == 0)
		return (NULL);

	/* Allocate memory for the array of tokens */
	tokens = malloc((1 + num_tokens) * sizeof(char *));
	if (!tokens)
		return (NULL);

	/* Split the string into tokens */
	for (i = 0, j = 0; j < num_tokens; j++)
	{
		while (is_delimiter(str[i], delimiter))
			i++;

		k = 0;
		while (!is_delimiter(str[i + k], delimiter) && str[i + k])
			k++;

		/* Allocate memory for the current token */
		tokens[j] = malloc((k + 1) * sizeof(char));
		if (!tokens[j])
		{
			for (k = 0; k < j; k++)
				free(tokens[k]);
			free(tokens);
			return (NULL);
		}

		/* Copy the current token into the array */
		for (m = 0; m < k; m++)
			tokens[j][m] = str[i++];
		tokens[j][m] = 0;
	}

	tokens[j] = NULL;
	return (tokens);
}

/**
 * split_string - splits a string into an array of substrings based on a delimiter
 * @str: the input string
 * @delimiter: the delimiter used to split the string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string(char *str, char delimiter)
{
	int i, j, k, m, num_substrings = 0;
	char **substrings;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	/* count the number of substrings */
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
		    (str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
			num_substrings++;

	if (num_substrings == 0)
		return (NULL);

	/* allocate memory for the substrings */
	substrings = malloc((1 + num_substrings) * sizeof(char *));
	if (!substrings)
		return (NULL);

	/* extract the substrings */
	for (i = 0, j = 0; j < num_substrings; j++)
	{
		while (str[i] == delimiter && str[i] != delimiter)
			i++;
		k = 0;
		while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
			k++;
		substrings[j] = malloc((k + 1) * sizeof(char));
		if (!substrings[j])
		{
			for (k = 0; k < j; k++)
				free(substrings[k]);
			free(substrings);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			substrings[j][m] = str[i++];
		substrings[j][m] = '\0';
	}
	substrings[j] = NULL;
	return (substrings);
}


