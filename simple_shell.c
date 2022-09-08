#include "shell.h"

unsigned int sig_flag;

/**
 * sig__ - handles ^C signal interupt
 * @uuv: unused variable (required for signal function prototype)
 *
 * Return: void
 */
static void sig__(int uuv)
{
	(void) uuv;
	if (sig_flag == 0)
		_puts("\n$ ");
	else
		_puts("\n");
}

/**
 * * main - main function for  shell
 * * @argc: no of arguments passed to main
 * * @argv: array of arguments passed to main
 * * @env: array of env variables
 * *
 * * Return: 0 or exit status, or ?
 */
int main(int argc __attribute__((unused)), char **argv, char **env)
{
	size_t len_buffer = 0;
	unsigned int is_pipe = 0, index;
	vars_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.argv = argv;
	vars.env = make_shell_env(env);
	signal(SIGINT, sig__);
	if (!isatty(STDIN_FILENO))
		is_pipe = 1;
	if (is_pipe == 0)
		_puts("$ ");
	sig_flag = 0;
	while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
	{
		sig_flag = 1;
		vars.count++;
		vars.commands = tokenize_buff(vars.buffer, ";");
		for (index = 0; vars.commands && vars.commands[index] != NULL; index++)
		{
			vars.av = tokenize_buff(vars.commands[index], "\n \t\r");
			if (vars.av && vars.av[0])
				if (builtin_checks(&vars) == NULL)
					check_path(&vars);
			free(vars.av);
		}
		free(vars.buffer);
		free(vars.commands);
		sig_flag = 0;
		if (is_pipe == 0)
			_puts("$ ");
		vars.buffer = NULL;
	}
	if (is_pipe == 0)
		_puts("\n");
	free_shell_env(vars.env);
	free(vars.buffer);
	exit(vars.status);
}

