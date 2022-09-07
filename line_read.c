#include <stdio.h>
#include <stdlib.h>
/**
 * *main-prototype..
 * *Return: 0
 */

int main(void)
{
	char *buffer = malloc(1024);
	size_t lenght = 1024;

	while (1)
	{
		printf("$ ");
		getline(&buffer, &lenght, stdin);
		prinf("%s", buffer);
	}
	return (0);
}

