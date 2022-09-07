#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * *main-prototype
 * *Return: 0
 */

int main(void)
{
	char *buffer = malloc(1024);
	size_t lenght = 1024;
	char *token;

	while (1)
	{
		printf("$ ");
		getline(&buffer, &lenght, stdin);
		printf("buffer getline: %s", buffer);
	}
	token = strtok(buffer, " ");
	while (token)
	{
		printf("buffer strtok: %s\n", token);
		token = strtok(NULL, " ");
	}
	return (0);
}

