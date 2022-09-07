#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <signal.h>
#define PROMPT "Shell $ "


/**
 * * struct builtin_d - Defines the built-ins functions.
 * * @built: The name of the build in command.
 * * @f: A pointer to the right built-in function.
 */
typedef struct builtin_d
{
	char *built;
	void (*f)(char *);
} builtin_t;

extern char **environ;

char **token_interacts(char *, const char *, int);
int count_tokens(char *, const char *);
char **tokenize_(int, char *, const char *);
void creates_child(char **, char *, int, char **);
void parse_ln(char *, size_t, int, char **);
char *p_finders(char *);
int str_len(char *);
int find_path(char *);
char **tokenize_path_(int, char *);
char *search_dir(char **, char *);
char *combine_path(char *, char *);
void free_double(char **);
void single_free(int, ...);



int built_in(char **, char *);
void (*check_built_ins(char *))(char *);
void exit_b(char *);
void env_var(char *);
void cd_passed(char *);



int _strcmp(char *, char *);
char *_strdup(char *);
void _print_str(char *, int);
int print_num(int);
int _write_char(char);



void print_error(char *, int, char *);
void print_exec_error(char *, int, char *);

#endif

