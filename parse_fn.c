#include "shell.h"
/**
 * * parse_ln - Parses --> command line looking for commands and argumements.
 * * This function it is also in charged of freeing memory that is not longer..
 * * needed by --> program.
 * * @line: A pointer to a string.. Will always be NULL upon function entry.
 * * @size: A holder for ..numbers of size_t. Will always be initilized to 0.
 * * @command_counter: A counter ..keeping track of how many commands have been
 * * entered into --> shell.
 * * @av: Name of --> program running --> shell
 */
void parse_ln(char *line, size_t size, int command_counter, char **av)
{
	int i;
	ssize_t read_len;
	int token_count_;
	char **param_arr;
	const char *delim = "\n\t ";

	token_count_ = 0;
	write(STDOUT_FILENO, PROMPT, str_len(PROMPT));
	read_len = getline(&line, &size, stdin);
	if (read_len != -1)
	{
		param_arr = token_interacts(line, delim, token_count_);
		if (param_arr[0] == NULL)
		{
			single_free(2, param_arr, line);
			return;
		}
		i = built_in(param_arr, line);
		if (i == -1)
			creates_child(param_arr, line, command_counter, av);
		for (i = 0; param_arr[i] != NULL; i++)
			free(param_arr[i]);
		single_free(2, param_arr, line);
	}
	else
		exit_b(line);
}

/**
 * * creates_child - Creates a child in order to execute another program.
 * * @param_arr: An array of pointers to strings containing --> possible name
 * * of a program and its parameters. This array is NULL terminated.
 * * @line: --> contents of --> read line.
 * * @count: A counter keeping track of how many commands have been entered
 * * into --> shell.
 * * @av: Name of --> program running --> shell
 */
void creates_child(char **param_arr, char *line, int count, char **av)
{
	pid_t id;
	int status;
	int i;
	int check;
	struct stat buf;
	char *tmp_command;
	char *command;

	id = fork();
	if (id == 0)
	{
		tmp_command = param_arr[0];
		command = p_finders(param_arr[0]);
		if (command == NULL)
		{

			check = stat(tmp_command, &buf);
			if (check == -1)
			{
				print_error(av[0], count, tmp_command);
				_print_str(": not found", 0);
				single_free(2, line, tmp_command);
				for (i = 1; param_arr[i]; i++)
					free(param_arr[i]);
				free(param_arr);
				exit(100);
			}

			command = tmp_command;
		}
		param_arr[0] = command;
		if (param_arr[0] != NULL)
		{
			if (execve(param_arr[0], param_arr, environ) == -1)
				print_exec_error(av[0], count, tmp_command);
		}
	}
	else
		wait(&status);
}

/**
 * * token_interacts - Meant to interact with other token functions, and make
 * * them more accessible to other parts of --> program.
 * * @line: A string containing --> raw user input.
 * * @delim: A constant string containing desired delimeter to tokenize_ line
 * * @token_count_: A holder for --> amount of tokens in a string.
 * * Return: Upon success an array of tokens representing --> command.
 * * Otherwise returns NULL.
 */
char **token_interacts(char *line, const char *delim, int token_count_)
{
	char **param_arr;

	token_count_ = count_tokens(line, delim);
	if (token_count_ == -1)
	{
		free(line);
		return (NULL);
	}
	param_arr = tokenize_(token_count_, line, delim);
	if (param_arr == NULL)
	{
		free(line);
		return (NULL);
	}

	return (param_arr);
}

/**
 * * tokenize_ - Separates a string into an array of tokens.
 * * on receiving function when using tokenize_.
 * * @token_count_: An integer representing --> amount of tokens in --> array.
 * * @line: String that is separated by an specified delimeter
 * * @delim: --> desired delimeter to separate tokens.
 * * Return: Upon success a NULL terminated array of pointer to strings.
 * * Otherwise returns NULL.
 */
char **tokenize_(int token_count_, char *line, const char *delim)
{
	int i;
	char **buffer;
	char *token;
	char *line_cp;

	line_cp = _strdup(line);
	buffer = malloc(sizeof(char *) * (token_count_ + 1));
	if (buffer == NULL)
		return (NULL);
	token = strtok(line_cp, delim);
	for (i = 0; token != NULL; i++)
	{
		buffer[i] = _strdup(token);
		token = strtok(NULL, delim);
	}
	buffer[i] = NULL;
	free(line_cp);
	return (buffer);
}

/**
 * * count_tokens - Counts tokens in --> passed string.
 * * @line: String that is separated by an specified delimeter
 * * @delim: --> desired delimeter to separate tokens.
 * * Return: Upon success --> total count of --> tokens. Otherwise -1.
 */
int count_tokens(char *line, const char *delim)
{
	char *str;
	char *token;
	int i;

	str = _strdup(line);
	if (str == NULL)
		return (-1);
	token = strtok(str, delim);
	for (i = 0; token != NULL; i++)
		token = strtok(NULL, delim);
	free(str);
	return (i);
}

