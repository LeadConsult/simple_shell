#include "shell.h"

/**
 * error_print - prints error messages to standard error
 * * @vars: pointer   to struct of variables
 * * @msg: message  to print
 * *
 * * Return: void
 */
void error_print(vars_t *vars, char *msg)
{
	char *count;

	_puts_2(vars->argv[0]);
	_puts_2(": ");
	count = unsignedint_str(vars->count);
	_puts_2(count);
	free(count);
	_puts_2(": ");
	_puts_2(vars->av[0]);
	if (msg)
	{
		_puts_2(msg);
	}
	else
		perror("");
}

/**
 * * _puts_2 - prints a string to standard error
 * * @str: string to print
 * *
 * * Return: void
 */
void _puts_2(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDERR_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * * unsignedint_str - converts an unsigned int to a string
 * * @count: unsigned int to convert
 * *
 * * Return: pointer to  converted string
 */
char *unsignedint_str(unsigned int count)
{
	char *numstr;
	unsigned int tmp, digits;

	tmp = count;
	for (digits = 0; tmp != 0; digits++)
		tmp /= 10;
	numstr = malloc(sizeof(char) * (digits + 1));
	if (numstr == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	numstr[digits] = '\0';
	for (--digits; count; --digits)
	{
		numstr[digits] = (count % 10) + '0';
		count /= 10;
	}
	return (numstr);
}

