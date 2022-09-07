#include "shell.h"

/**
 * * tokenize_buff - tokenizes a buffer with a delimiter
 * * @buffer: buffer to tokenize_buff
 * * @delimiter: delimiter to tokenize_buff along
 * *
 * * Return: pointer to an array of pointers to  tokens
 */
char **tokenize_buff(char *buffer, char *delimiter)
{
	char **tokens = NULL;
	size_t index = 0, mcount = 10;

	if (buffer == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * mcount);
	if (tokens == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((tokens[index] = cus_strtok(buffer, delimiter)) != NULL)
	{
		index++;
		if (index == mcount)
		{
			tokens = realloc_p(tokens, &mcount);
			if (tokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		buffer = NULL;
	}
	return (tokens);
}

