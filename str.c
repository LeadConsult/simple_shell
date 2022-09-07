#include "shell.h"

/**
 * * _puts - writes a string to standard output
 * * @str: string to write
 * *
 * * Return: no of chars printed or -1 on failure
 */
ssize_t _puts(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDOUT_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (len);
}

/**
 * * _strdup - returns pointer to new mem alloc space which contains copy
 * * @strtodup: string to be duplicated
 * * Return: a pointer to  new duplicated string
 */
char *_strdup(char *strtodup)
{
	char *copy;

	int len, index;

	if (strtodup == 0)
		return (NULL);

	for (len = 0; strtodup[len]; len++)
		;
	copy = malloc((len + 1) * sizeof(char));

	for (index = 0; index <= len; index++)
		copy[index] = strtodup[index];

	return (copy);
}

/**
 * * _strcmpr - compares two strings
 * * @strcmp1: first string, of two, to be compared in length
 * * @strcmp2: second string, of two, to be compared
 * * Return: 0 on success, anything else is a failure
 */
int _strcmpr(char *strcmp1, char *strcmp2)
{
	int index;

	index = 0;
	while (strcmp1[index] == strcmp2[index])
	{
		if (strcmp1[index] == '\0')
			return (0);
		index++;
	}
	return (strcmp1[index] - strcmp2[index]);
}

/**
 * * _strcat - concatenates two strings
 * * @strc1: first string
 * * @strc2: second string
 * * Return: pointer
 */
char *_strcat(char *strc1, char *strc2)
{
	char *newstring;
	unsigned int len1, len2, newlen, index, j;

	len1 = 0;
	len2 = 0;
	if (strc1 == NULL)
		len1 = 0;
	else
	{
		for (len1 = 0; strc1[len1]; len1++)
			;
	}
	if (strc2 == NULL)
		len2 = 0;
	else
	{
		for (len2 = 0; strc2[len2]; len2++)
			;
	}
	newlen = len1 + len2 + 2;
	newstring = malloc(newlen * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	for (index = 0; index < len1; index++)
		newstring[index] = strc1[index];
	newstring[index] = '/';
	for (j = 0; j < len2; j++)
		newstring[index + 1 + j] = strc2[j];
	newstring[len1 + len2 + 1] = '\0';
	return (newstring);
}

/**
 * * _strlen - returns  length of a string
 * * @str: string to be measured
 * * Return: length of string
 */
unsigned int _strlen(char *str)
{
	unsigned int len;

	len = 0;

	for (len = 0; str[len]; len++)
		;
	return (len);
}

