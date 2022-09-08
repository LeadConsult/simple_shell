#include "shell.h"

/**
 * make_shell_env - make  shell environment from  environment passed to main
 * * @env: environment passed to main
 * *
 * * Return: pointer to  new environment
 */
char **make_shell_env(char **env)
{
	char **new_env = NULL;
	size_t index;

	for (index = 0; env[index] != NULL; index++)
		;
	new_env = malloc(sizeof(char *) * (index + 1));
	if (new_env == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (index = 0; env[index] != NULL; index++)
		new_env[index] = _strdup(env[index]);
	new_env[index] = NULL;
	return (new_env);
}

/**
 * * free_shell_env - free  shell's environment
 * * @env: shell's environment
 * *
 * * Return: void
 */
void free_shell_env(char **env)
{
	unsigned int index;

	for (index = 0; env[index] != NULL; index++)
		free(env[index]);
	free(env);
}

