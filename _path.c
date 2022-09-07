#include "shell.h"

/**
 * path_exe - executes a command in  path
 * @command: full path to  command
 * @vars: pointer to struct of variables
 *
 * Return: 0 on succcess, 1 on failure
 */
int path_exe(char *command, vars_t *vars)
{
	pid_t child_pid;

	if (access(command, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
			error_print(vars, NULL);
		if (child_pid == 0)
		{
			if (execve(command, vars->av, vars->env) == -1)
				error_print(vars, NULL);
		}
		else
		{
			wait(&vars->status);
			if (WIFEXITED(vars->status))
				vars->status = WEXITSTATUS(vars->status);
			else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
				vars->status = 130;
			return (0);
		}
		vars->status = 127;
		return (1);
	}
	else
	{
		error_print(vars, ": Permission denied\n");
		vars->status = 126;
	}
	return (0);
}

/**
 * find_path - finds  PATH variable
 * @env: array of environment variables
 *
 * Return: pointer to  node that contains  PATH, or NULL on failure
 */
char *find_path(char **env)
{
	char *path = "PATH=";
	unsigned int index, j;

	for (index = 0; env[index] != NULL; index++)
	{
		for (j = 0; j < 5; j++)
			if (path[j] != env[index][j])
				break;
		if (j == 5)
			break;
	}
	return (env[index]);

}

/**
 * check_path - checks if  command is in  PATH
 * @vars: variables
 *
 * Return: void
 */
void check_path(vars_t *vars)
{
	char *path, *path_dup = NULL, *check = NULL;
	unsigned int index = 0, r = 0;
	char **path_tokens;
	struct stat buf;

	if (check_dir(vars->av[0]))
		r = exe_cwd(vars);
	else
	{
		path = find_path(vars->env);
		if (path != NULL)
		{
			path_dup = _strdup(path + 5);
			path_tokens = tokenize_buff(path_dup, ":");
			for (index = 0; path_tokens && path_tokens[index]; index++, free(check))
			{
				check = _strcat(path_tokens[index], vars->av[0]);
				if (stat(check, &buf) == 0)
				{
					r = path_exe(check, vars);
					free(check);
					break;
				}
			}
			free(path_dup);
			if (path_tokens == NULL)
			{
				vars->status = 127;
				exit_prog(vars);
			}
		}
		if (path == NULL || path_tokens[index] == NULL)
		{
			error_print(vars, ": not found\n");
			vars->status = 127;
		}
		free(path_tokens);
	}
	if (r == 1)
		exit_prog(vars);
}

/**
 * exe_cwd - executes  command in  current working directory
 * @vars: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */
int exe_cwd(vars_t *vars)
{
	pid_t child_pid;
	struct stat buf;

	if (stat(vars->av[0], &buf) == 0)
	{
		if (access(vars->av[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				error_print(vars, NULL);
			if (child_pid == 0)
			{
				if (execve(vars->av[0], vars->av, vars->env) == -1)
					error_print(vars, NULL);
			}
			else
			{
				wait(&vars->status);
				if (WIFEXITED(vars->status))
					vars->status = WEXITSTATUS(vars->status);
				else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
					vars->status = 130;
				return (0);
			}
			vars->status = 127;
			return (1);
		}
		else
		{
			error_print(vars, ": Permission denied\n");
			vars->status = 126;
		}
		return (0);
	}
	error_print(vars, ": not found\n");
	vars->status = 127;
	return (0);
}

/**
 * check_dir - checks if  command is a part of a path
 * @str: command
 *
 * Return: 1 on success, 0 on failure
 */
int check_dir(char *str)
{
	unsigned int index;

	for (index = 0; str[index]; index++)
	{
		if (str[index] == '/')
			return (1);
	}
	return (0);
}

