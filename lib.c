#include "shell.h"

/**
 * * _strcmp - compares two strings..
 * * @s1: First string..
 * * @s2: Second string..
 * * Return: 0 if strings match. -1 Otherwise.
 */
int _strcmp(char *s1, char *s2)
{
	int index;

	if (str_len(s1) != str_len(s2))
		return (-1);
	for (index = 0; s1[index] != '\0'; index++)
	{
		if (s1[index] != s2[index])
			return (-1);
	}
	return (0);
}

/**
 * * _strdup - create a copy of a string
 * * @src: Contains the original string
 * * Return: Gives back the copy of string
 */
char *_strdup(char *src)
{
	int index;
	int len;
	char *dest;

	len = str_len(src);
	dest = malloc(sizeof(char) * (len + 1));

	for (index = 0; src[index] != '\0'; index++)
		dest[index] = src[index];
	dest[index] = '\0';
	return (dest);
}

/**
 * * _print_str - Prints a string character by character.
 * * @str: String to be printed. If the string is NULL it will print (null)
 * * @new_line: If integer is 0 a new line will be printed.
 * * Otherwise a new line
 * * will not be printed.
 */
void _print_str(char *str, int new_line)
{
	int index;

	if (str == NULL)
		str = "(null)";
	for (index = 0; str[index] != '\0'; index++)
		write(STDOUT_FILENO, &str[index], 1);
	if (new_line == 0)
		write(STDOUT_FILENO, "\n", 1);
}

/**
 * * _write_char - Writes a character to stdout
 * * @c: Character that will be written to stdout
 * * Return: Upon success how many characters were written.
 */
int _write_char(char c)
{
	return (write(1, &c, 1));
}

