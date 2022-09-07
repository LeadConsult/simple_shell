#include "shell.h"

/**
 * * p_finders - Acts as an interface for functions that will be able to
 * * find the full path of a program.
 * * @command: Represents a command. For example ls, echo, pwd, etc.
 * * Return: Upon success a string with the full path of the program.
 * * for example /bin/ls, /bin/echo, etc. Otherwise returns NULL.
 */
char *p_finders(char *command)
{
	char *str = "PATH";
	char *constructed;
	char **path_tokens;
	int index;
	char *dir;

	index = find_path(str);
	path_tokens = tokenize_path_(index, str);
	if (path_tokens == NULL)
		return (NULL);

	dir = search_dir(path_tokens, command);
	if (dir == NULL)
	{
		free_double(path_tokens);
		return (NULL);
	}

	constructed = combine_path(dir, command);
	if (constructed == NULL)
	{
		free_double(path_tokens);
		return (NULL);
	}

	free_double(path_tokens);

	return (constructed);
}
/**
 * * find_path - Finds the index of an environmental variable.
 * * @str: Environmental variable that needs to be found.
 * * Return: Upon success returns the index of the environmental variable.
 * * otherwise returns -1.
 */
int find_path(char *str)
{
	int x;
	int len;
	int y;

	len = str_len(str);
	for (x = 0; environ[x] != NULL; x++)
	{
		for (y = 0; y < len; y++)
		{
			if (environ[x][y] != str[y])
				break;
		}
		if (y == len && environ[x][y] == '=')
			return (x);
	}
	return (-1);
}

/**
 * * tokenize_path_ - Separates a string representing paths as an array
 * * of strings contining the path directories.
 * * @index: Index of the path in the environment variables.
 * * @str: string to separate and tokenize_.
 * * Return: Upon success a NULL terminated array of pointer to strings.
 * * Otherwise returns NULL. Note!: Do not forget to free alocated
 * * memory on receiving function or when possible.
 */
char **tokenize_path_(int index, char *str)
{
	char *env_var;
	int token_count_;
	const char *delim = ":\n";
	char **path_tokens;
	int len;

	len = str_len(str);
	token_count_ = 0;

	env_var = environ[index] + (len + 1);
	path_tokens = token_interacts(env_var, delim, token_count_);
	if (path_tokens == NULL)
		return (NULL);

	return (path_tokens);
}

/**
 * * search_dir - Looks through directories stored in path_tokens for a
 * * specific file. aka commmand.
 * * @path_tokens: A pointer to an array of strings representing the different
 * * paths contained in the PATH environmental varible.
 * * @command: Represents a command. For example ls, echo, pwd, /bin/ls etc.
 * * Return: Upon success a string with the upper most dir containing
 * * the command file. Otherwise returns NULL.
 */
char *search_dir(char **path_tokens, char *command)
{
	int x, s;
	char *cwd;
	char *buf;
	size_t size;
	struct stat stat_buf;

	buf = NULL;
	size = 0;
	cwd = getcwd(buf, size);
	if (cwd == NULL)
		return (NULL);
	if (command[0] == '/')
		command = command + 1;
	for (x = 0; path_tokens[x] != NULL; x++)
	{
		s = chdir(path_tokens[x]);
		if (s == -1)
		{
			perror("ERROR!");
			return (NULL);
		}
		s = stat(command, &stat_buf);
		if (s == 0)
		{
			chdir(cwd);
			free(cwd);
			return (path_tokens[x]);
		}
	}
	chdir(cwd);
	free(cwd);
	return (NULL);
}

/**
 * * combine_path - Combines two strings one representing the path dir and
 * * one representing the command file.
 * * @dir: Represents a dir in the path.
 * * @command: Represents a file in a dir of the path.
 * * Return: Upon success a string representing the full path of a command.
 * * Otherwise NULL.
 */
char *combine_path(char *dir, char *command)
{
	int x, y;
	int dir_len;
	int command_len;
	int len;
	char *built;

	if (dir == NULL || command == NULL)
		return (NULL);
	dir_len = str_len(dir) + 1;
	command_len = str_len(command) + 1;
	len = dir_len + command_len;

	built = malloc(sizeof(char) * len);
	if (built == NULL)
		return (NULL);

	for (x = 0; x < len; x++)
	{
		for (y = 0; dir[y] != '\0'; y++, x++)
			built[x] = dir[y];
		built[x] = '/';
		x++;
		for (y = 0; command[y] != '\0'; y++, x++)
			built[x] = command[y];
	}
	built[--x] = '\0';
	return (built);
}

