#include "shell.h"

/**
 * * new_env_var - create a new environment variable
 * * @vars: pointer to struct of variables
 * *
 * * Return: void
 */
void new_env_var(vars_t *vars)
{
	unsigned int index;
	char **new_env;

	for (index = 0; vars->env[index] != NULL; index++)
		;
	new_env = malloc(sizeof(char *) * (index + 2));
	if (new_env == NULL)
	{
		error_print(vars, NULL);
		vars->status = 127;
		exit_prog(vars);
	}
	for (index = 0; vars->env[index] != NULL; index++)
		new_env[index] = vars->env[index];
	new_env[index] = add_new_env(vars->av[1], vars->av[2]);
	if (new_env[index] == NULL)
	{
		error_print(vars, NULL);
		free(vars->buffer);
		free(vars->commands);
		free(vars->av);
		free_shell_env(vars->env);
		free(new_env);
		exit(127);
	}
	new_env[index + 1] = NULL;
	free(vars->env);
	vars->env = new_env;
}

/**
 * * find_env_var - finds an environment variable
 * * @env: array of environment variables
 * * @key: environment variable to find
 * *
 * * Return: pointer to address of  environment variable
 */
char **find_env_var(char **env, char *key)
{
	unsigned int index, j, len;

	len = _strlen(key);
	for (index = 0; env[index] != NULL; index++)
	{
		for (j = 0; j < len; j++)
			if (key[j] != env[index][j])
				break;
		if (j == len && env[index][j] == '=')
			return (&env[index]);
	}
	return (NULL);
}

/**
 * * add_new_env - create a new environment variable string
 * * @key: variable name
 * * @value: variable value
 * *
 * * Return: pointer to  new string;
 */
char *add_new_env(char *key, char *value)
{
	unsigned int len1, len2, index, j;
	char *new;

	len1 = _strlen(key);
	len2 = _strlen(value);
	new = malloc(sizeof(char) * (len1 + len2 + 2));
	if (new == NULL)
		return (NULL);
	for (index = 0; key[index] != '\0'; index++)
		new[index] = key[index];
	new[index] = '=';
	for (j = 0; value[j] != '\0'; j++)
		new[index + 1 + j] = value[j];
	new[index + 1 + j] = '\0';
	return (new);
}

/**
 * * _atoi - converts a string into an integer
 * * @str: string to convert
 * *
 * * Return:  integer value, or -1 if an error occurs
 */
int _atoi(char *str)
{
	unsigned int index, digits;
	int num = 0, num_test;

	num_test = INT_MAX;
	for (digits = 0; num_test != 0; digits++)
		num_test /= 10;
	for (index = 0; str[index] != '\0' && index < digits; index++)
	{
		num *= 10;
		if (str[index] < '0' || str[index] > '9')
			return (-1);
		if ((index == digits - 1) && (str[index] - '0' > INT_MAX % 10))
			return (-1);
		num += str[index] - '0';
		if ((index == digits - 2) && (str[index + 1] != '\0') &&
				(num > INT_MAX / 10))
			return (-1);
	}
	if (index > digits)
		return (-1);
	return (num);
}

