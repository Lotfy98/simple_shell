#include "shell.h"
/**
 * free_memory - entry point
 *@ptr: pointer
 *Return: void
 */
void free_memory(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
