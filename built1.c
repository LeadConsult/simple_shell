#include "shell.h"

/**
 * * builtin_checks - checks if  command is a builtin
 * * @vars: variables
 * * Return: pointer to  function or NULL
 */
void (*builtin_checks(vars_t *vars))(vars_t *vars)
{
	unsigned int index;
	builtins_t check[] = {
		{"exit", exit_prog},
		{"env", current_env},
		{"setenv", new_env},
		{"unsetenv", rem_env_var},
		{NULL, NULL}
	};

	for (index = 0; check[index].f != NULL; index++)
	{
		if (_strcmpr(vars->av[0], check[index].name) == 0)
			break;
	}
	if (check[index].f != NULL)
		check[index].f(vars);
	return (check[index].f);
}

/**
 * * exit_prog - exit program
 * * @vars: variables
 * * Return: void
 */
void exit_prog(vars_t *vars)
{
	int status;

	if (_strcmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			error_print(vars, ": Illegal no: ");
			_puts_2(vars->av[1]);
			_puts_2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_shell_env(vars->env);
	exit(vars->status);
}

/**
 * * current_env - prints  current environment
 * * @vars: struct of variables
 * * Return: void.
 */
void current_env(vars_t *vars)
{
	unsigned int index;

	for (index = 0; vars->env[index]; index++)
	{
		_puts(vars->env[index]);
		_puts("\n");
	}
	vars->status = 0;
}

/**
 * * new_env - create a new environment variable, or edit an existing variable
 * * @vars: pointer to struct of variables
 * *
 * * Return: void
 */
void new_env(vars_t *vars)
{
	char **key;
	char *var;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		error_print(vars, ": Incorrect no of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_env_var(vars->env, vars->av[1]);
	if (key == NULL)
		new_env_var(vars);
	else
	{
		var = add_new_env(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			error_print(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			free_shell_env(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}

/**
 * * rem_env_var - remove an environment variable
 * * @vars: pointer to a struct of variables
 * *
 * * Return: void
 */
void rem_env_var(vars_t *vars)
{
	char **key, **new_env;

	unsigned int index, j;

	if (vars->av[1] == NULL)
	{
		error_print(vars, ": Incorrect no of arguments\n");
		vars->status = 2;
		return;
	}
	key = find_env_var(vars->env, vars->av[1]);
	if (key == NULL)
	{
		error_print(vars, ": No variable to unset");
		return;
	}
	for (index = 0; vars->env[index] != NULL; index++)
		;
	new_env = malloc(sizeof(char *) * index);
	if (new_env == NULL)
	{
		error_print(vars, NULL);
		vars->status = 127;
		exit_prog(vars);
	}
	for (index = 0; vars->env[index] != *key; index++)
		new_env[index] = vars->env[index];
	for (j = index + 1; vars->env[j] != NULL; j++, index++)
		new_env[index] = vars->env[j];
	new_env[index] = NULL;
	free(*key);
	free(vars->env);
	vars->env = new_env;
	vars->status = 0;
}

