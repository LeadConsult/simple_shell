#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * * main - exercise: fork_wait_execve
 * *
 * * Return: Always 0
 */

int main(void)
{
	pid_t p_pid;
	pid_t c_pid = 1;
	int i = 0;
	int status;
	char *argv[] = {"bin/ls", "-l", "tmp/", NULL};

	p_pid = getpid();
	while (i <= 4 && (c_pid != 0))
	{
		c_pid = fork();
		if (c_pid == -1)
		{
			printf("error");
			return (1);
		}
		wait(&status);
		i++;
	}
	if (c_pid == 0)
	{
		printf("--------------------------------\n\n");
		printf("ID: %u\n\nID PADRE: %u\n\n", getpid(), getppid());
		printf("--------------------------------\n\n");

	}
	else
	{
		printf("%u $$: %u\n", p_pid, c_pid);
	}
	if (execve(argv[0], argv, NULL) == -1)
	{
		/*perror("ERROR:");*/
	}
	return (0);
}

