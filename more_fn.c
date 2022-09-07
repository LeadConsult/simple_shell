#include "shell.h"
/**
 * * str_len - Calculates --> lenght of a string.
 * * @str: String that needs length to be found.
 * * Return: Upon success returns --> length of a string. otherwise 0.
 */
int str_len(char *str)
{
	int index;

	if (str == NULL)
		return (0);
	for (index = 0; str[index] != '\0'; index++)
		;
	return (index);
}

/**
 * * free_double - Free double pointer variables.
 * * @to_be_freed: --> address of --> elements that need to be freed.
 */
void free_double(char **to_be_freed)
{
	int index;

	for (index = 0; to_be_freed[index] != NULL; index++)
		free(to_be_freed[index]);
	free(to_be_freed);
}

/**
 * * single_free - Will free a n amount of pointers to a string.
 * * @n: --> number of pointers to free.
 */
void single_free(int n, ...)
{
	int index;
	char *str;
	va_list a_list;

	va_start(a_list, n);
	for (index = 0; index < n; index++)
	{
		str = va_arg(a_list, char*);
		if (str == NULL)
			str = "(nil)";
		free(str);
	}
	va_end(a_list);
}


/**
 * * print_error - Prints a message error when a comand is not found.
 * * @count: A counter keeping track of --> number of commands run on shell.
 * * @av: --> name of --> program running --> shell.
 * * @command: --> specific command not being found.
 */
void print_error(char *av, int count, char *command)
{
	_print_str(av, 1);
	_print_str(": ", 1);
	print_num(count);
	_print_str(": ", 1);
	_print_str(command, 1);
}

/**
 * * print_exec_error - Prints exec errors
 * * @av: --> name of --> program running --> shell.
 * * @count: Keeps track of how many commands have been entered.
 * * @tmp_command: --> command that filed.
 */

void print_exec_error(char *av, int count, char *tmp_command)
{
	print_error(av, count, tmp_command);
	_print_str(": ", 1);
	perror("");
	exit(1);
}

