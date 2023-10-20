#include "shell.h"
/**
 * parse_args - Parses the arguments from the command string
 * @cmd: The command string to parse
 *
 * Return: A dynamically allocated array of strings,
 *where each string is an argument
 */
char **parse_args(char *cmd)
{
	char *arg;
	char **args = malloc(MAX_ARGS * sizeof(char *));
	int i = 0;

	args[i++] = cmd;
	/* Use whitespace as delimiter */
	while ((arg = _strtok(NULL, " \t\n")) != NULL)
	{
		/* Dynamically allocate memory for each argument */
		args[i] = malloc((_strlen(arg) + 1) * sizeof(char));
		_strcpy(args[i], arg);
		i++;
	}
	args[i] = NULL; /* Properly terminate the args array */
	return (args);
}
/**
 * free_args - Frees the dynamically allocated memory for
 *each argument and the argument array itself
 * @args: The argument array to free
 *
 * Return: Nothing
 */
void free_args(char **args)
{
	int i;

	for (i = 1; args[i] != NULL; i++)
		free(args[i]);
	free(args); /* Free the dynamically allocated memory */
}
