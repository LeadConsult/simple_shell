#include <stdio.h>
#include <unistd.h>

/**
 * * main - execve example....
 * *
 * * Return: Always 0.
 */

int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

	printf("Pre execve\n");
	if (execve(argv[0], argv, NULL) == -1)
	{
		perror("Error: ");
	}
	printf("Post execve \n");
	return (0);
}

