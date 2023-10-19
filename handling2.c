#include "shell.h"
/**
 * _memcpy - function to copy memory area
 * @dest: destination memory area
 * @src: source memory area
 * @n: number of bytes to copy
 *
 * Description: This function copies n bytes from memory
 *area src to memory area dest.
 *
 * Return: returns a pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int x = 0;

	while (x < n)
	{
		dest[x] = src[x];
		x++;
	}
	return (dest);
}
/**
 * trim - function to trim leading and trailing whitespace characters
 * @str: string to trim
 *
 * Description: This function trims leading and trailing
 *whitespace characters from a string.
 *
 * Return: returns a pointer to the trimmed string
 */
char *trim(char *str)
{
	char *end;

	while (_isspace((unsigned char)*str))
		str++;
	end = str + _strlen(str) - 1;
	while (end > str && _isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (str);
}
/**
 * _strdup - function to duplicate a string
 * @str: string to duplicate
 *
 * Description: This function duplicates a string.
 * It allocates memory for the duplicated string.
 *
 * Return: returns a pointer to the duplicated string
 *if successful, otherwise NULL
 */
char *_strdup(char *str)
{
	char *xx;
	unsigned int x;

	if (str == NULL)
		return (NULL);
	x = _strlen(str) + 1;
	xx = malloc(x);
	if (xx == NULL)
	{
		free(xx);
		return (NULL);
	}
	_memcpy(xx, str, x);
	return (xx);
}
/**
 * handle_cp - Function to handle the cp command
 * @args: An array of arguments for the cp command
 * @environ: The environment variables
 *
 * This function handles the cp command. It uses execve to execute
 *the cp command with the provided arguments and environment variables.
 */
void handle_cp(char **args, char **environ)
{
	char *cmd_path = "/bin/cp";
	(void)args;
	(void)environ;
	execute_command(cmd_path, args, environ);
}
