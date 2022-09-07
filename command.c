#include "shell.h"

/**
 * * cd_passed - Changes current working directory to parameter passed to cd
 * * if no parameter is passed, it will change directory to HOME.
 * * @line: A string representing --> input from --> user.
 */
void cd_passed(char *line)
{
	int i;
	int token_count_;
	char **param_arr;
	const char *delim = "\n\t ";

	token_count_ = 0;
	param_arr = token_interacts(line, delim, token_count_);
	if (param_arr[0] == NULL)
	{
		single_free(2, param_arr, line);
		return;
	}
	if (param_arr[1] == NULL)
	{
		i = find_path("HOME");
		chdir((environ[i]) + 5);
	}
	else if (_strcmp(param_arr[1], "-") == 0)
		_print_str(param_arr[1], 0);

	else
		chdir(param_arr[1]);
	free_double(param_arr);
}

/**
 * * env_var - Prints all --> environmental variables in --> current shell.
 * * @line: A string representing --> input from --> user.
 */
void env_var(__attribute__((unused))char *line)
{
	int i;
	int j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '\0'; j++)
			write(STDOUT_FILENO, &environ[i][j], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * * exit_b - Exits --> shell. After freeing allocated resources.
 * * @line: A string representing --> input from --> user.
 */
void exit_b(char *line)
{
	free(line);
	_print_str("\n", 1);
	exit(1);
}

/**
 * * check_built_ins - Finds --> right function needed for execution.
 * * @str: --> name of --> function that is needed.
 * * Return: Upon sucess a pointer to a void function. Otherwise NULL.
 */
void (*check_built_ins(char *str))(char *str)
{
	int i;

	builtin_t buildin[] = {
		{"exit", exit_b},
		{"env", env_var},
		{"cd", cd_passed},
		{NULL, NULL}
	};

	for (i = 0; buildin[i].built != NULL; i++)
	{
		if (_strcmp(str, buildin[i].built) == 0)
		{
			return (buildin[i].f);
		}
	}
	return (NULL);
}

/**
 * * built_in_fn - Checks for built-in functions.
 * * @command: An array of all --> arguments passed to --> shell.
 * * @line: A string representing --> input from --> user.
 * * Return: If function is found 0. Otherwise -1.
 */
int built_in_fn(char **command, char *line)
{
	void (*build)(char *);

	build = check_built_ins(command[0]);
	if (build == NULL)
		return (-1);
	if (_strcmp("exit", command[0]) == 0)
		free_double(command);
	build(line);
	return (0);
}

