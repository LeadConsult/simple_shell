#include <stdio.h>
#include <stdlib.h>
/**
 * *main-prototype
 * *@ac:argument count
 * *@av:argument vector
 * *Return: 0
 */
int main(int ac, char **av)
{
	int index = 0;

	while (av[index])
	{
		printf("%s ", av[index]);
		index++;
	}
	printf("\n");
	return (0);
}

