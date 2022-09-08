#include "shell.h"

/**
 * * realloc_p - reallocates a pointer to double  space
 * * @ptr: pointer to  old array
 * * @size: pointer to no of elements in  old array
 * *
 * Return: pointer to  new array
 */
char **realloc_p(char **ptr, size_t *size)
{
	char **new;
	size_t index;

	new = malloc(sizeof(char *) * ((*size) + 10));
	if (new == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (index = 0; index < (*size); index++)
	{
		new[index] = ptr[index];
	}
	*size += 10;
	free(ptr);
	return (new);
}

