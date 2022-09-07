#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

/**
 * * struct variables - variables
 * * @av: command line arguments
 * * @buffer: buffer of command
 * * @env: environment variables
 * * @count: count of commands entered
 * * @argv: arguments at opening of shell
 * * @status: exit status
 * * @commands: commands to execute
 */
typedef struct variables
{
	char **av;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int status;
	char **commands;
} vars_t;

/**
 * * struct builtins - struct for  builtin functions
 * * @name: name of builtin command
 * * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(vars_t *);
} builtins_t;

char **make_shell_env(char **env);
void free_shell_env(char **env);

ssize_t _puts(char *str);
char *_strdup(char *strtodup);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);

char **tokenize_buff(char *buffer, char *delimiter);
char **realloc_p(char **ptr, size_t *size);
char *cus_strtok(char *str, const char *delim);

void (*builtin_checks(vars_t *vars))(vars_t *vars);
void exit_prog(vars_t *vars);
void _env(vars_t *vars);
void new_env(vars_t *vars);
void rem_env_var(vars_t *vars);

void new_env_var(vars_t *vars);
char **find_env_var(char **env, char *key);
char *add_new_env(char *key, char *value);
int _atoi(char *str);

void check_path(vars_t *vars);
int path_exe(char *command, vars_t *vars);
char *find_path(char **env);
int exe_cwd(vars_t *vars);
int check_dir(char *str);

void error_print(vars_t *vars, char *msg);
void _puts_2(char *str);
char *unsignedint_str(unsigned int count);

#endif /* _SHELL_H_ */

