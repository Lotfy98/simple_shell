#include "shell.h"
/**
 * _getenv - Get the value of an environment variable.
 * @name: The name of the environment variable.
 * @environ: The environment variables.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */

char *_getenv(char *name, char **environ)
{
	size_t len = _strlen(name); /* Get the length of the name. */

	/* Iterate through the environment variables. */
	while (*environ != NULL)
	{
		if (_strncmp(*environ, name, len) == 0 && (*environ)[len] == '=')
			return (&(*environ)[len + 1]);
		environ++;
	}

	/* Return NULL if the variable is not found. */
	return (NULL);
}
/**
 * _getpath - Get the full path to an executable command.
 * @cmd: The name of the command.
 * @environ: The environment variables.
 *
 * Return: The full path to the command, NULL if not found or not executable.
 */
char *_getpath(char *cmd, char **environ)
{
	/* Get the system's PATH. */
	char *path = _getenv("PATH", environ);
	/* Make a copy of the PATH to tokenize. */
	char *path_copy = _strdup(path);
	/* Tokenize the PATH, splitting on colons. */
	char *dir = _strtok(path_copy, ":");
	char *file_path;

	/* Iterate over each directory in the PATH. */
	while (dir != NULL)
	{
		/* Allocate space for the file path. */
		file_path = malloc(_strlen(dir) + _strlen(cmd) + 2);
		/* Construct the file path. */
		_strcpy(file_path, dir);
		_strcat(file_path, "/");
		_strcat(file_path, cmd);

		/* Check if the file exists and is executable. */
		if (access(file_path, X_OK) == 0)
		{
			/* If it is, clean up and return the file path. */
			free(path_copy);
			return (file_path);
		}

		/* If it's not, free the file path and get the next directory. */
		free(file_path);
		dir = _strtok(NULL, ":");
	}

	/* If no executable file was found, clean up and return NULL. */
	free(path_copy);
	return (NULL);
}
/**
 * _isspace - Check if a character is a whitespace character.
 * @c: The character to check.
 *
 * Return: 1 if the character is a whitespace character, 0 otherwise.
 */

int _isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}
/**
 * _getline - Read a line of text from a file stream.
 * @lineptr: A pointer to the line buffer or NULL for dynamic allocation.
 * @n: A pointer to the size of the buffer or 0 for dynamic allocation.
 * @stream: The input file stream.
 *
 * Return: The number of characters read, -1 on error or EOF.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t i = 0;
	size_t old_n;
	char c;
	char *new_lineptr;
	(void)stream;

	if (*lineptr == NULL)
	{
		*lineptr = malloc(MAX_COMMAND_LENGTH);
		*n = MAX_COMMAND_LENGTH;
	}
	while ((c = _getchar()) != '\n')
	{
		if (i >= *n - 1)
		{
			old_n = *n;
			*n *= 2;
			new_lineptr = _realloc(*lineptr, old_n, *n);
			if (new_lineptr == NULL)
				return (-1);
			*lineptr = new_lineptr;
		}
		(*lineptr)[i++] = c;
	}
	(*lineptr)[i] = '\0';
	return (i);
}

