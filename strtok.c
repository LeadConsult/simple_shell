#include "shell.h"
/**
 * * check_matchs - checks if a character matches any in a string
 * @c: character to check
 * * @str: string to check
 * *
 * * Return: 1 if match, 0 if not
 */
unsigned int check_matchs(char c, const char *str)
{
	unsigned int index;

	for (index = 0; str[index] != '\0'; index++)
	{
		if (c == str[index])
			return (1);
	}
	return (0);
}

/**
 * * cus_strtok - custom strtok
 * * @str: string to tokenize_buff
 * * @delim: delimiter to tokenize_buff against
 * *
 * * Return: pointer to  next token or NULL
 */
char *cus_strtok(char *str, const char *delim)
{
	static char *token_start;
	static char *next_token;
	unsigned int index;

	if (str != NULL)
		next_token = str;
	token_start = next_token;
	if (token_start == NULL)
		return (NULL);
	for (index = 0; next_token[index] != '\0'; index++)
	{
		if (check_matchs(next_token[index], delim) == 0)
			break;
	}
	if (next_token[index] == '\0' || next_token[index] == '#')
	{
		next_token = NULL;
		return (NULL);
	}
	token_start = next_token + index;
	next_token = token_start;
	for (index = 0; next_token[index] != '\0'; index++)
	{
		if (check_matchs(next_token[index], delim) == 1)
			break;
	}
	if (next_token[index] == '\0')
		next_token = NULL;
	else
	{
		next_token[index] = '\0';
		next_token = next_token + index + 1;
		if (*next_token == '\0')
			next_token = NULL;
	}
	return (token_start);
}

