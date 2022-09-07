#include <stdio.h>
#include <unistd.h>

/**
 * * main - fork example.....
 * *
 * * Return: Always 0.
 */

int main(void)
{
	pid_t p_pid;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error: ");
		return (1);
	}
	p_pid = getpid();
	printf("Pid is %u\n", p_pid);
	if (child_pid == 0)
	{
		printf("(%u) No!!\n", p_pid);
	}
	else
	{
		printf("(%u) %u, Parent\n", p_pid, child_pid);
	}
	return (0);
}

