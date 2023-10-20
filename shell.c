#include "shell.h"
/**
 * main - Main function for the shell.
 * @argc: Argument count.
 * @argv: Argument vector.
 * @environ: Environment variables.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char **argv, char **environ)
{
	char command[MAX_COMMAND_LENGTH];
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	(void)argc; 
	(void)argv; 

	if (!isatty(STDIN_FILENO))
	{
		if ((nread = _getline(&line, &len, stdin)) != -1)
		{
			if (nread != 0)
			{
				_strcpy(command, line);
				handle_command(command, environ);

				free(line);
				line = NULL;
			}
<<<<<<< HEAD
			_strcpy(command, line); /* Copy the line. */
			handle_command(command, environ); /* Handle the command. */
		/*	free(line);*/ /* Free the memory allocated by getline. */
		/*	line = NULL;*/ /* Prevent dangling pointers. */
		/*	break;*/ /* Exit the loop after executing the command. */
=======
>>>>>>> c594e3f56a1f4c1324459aa5e163b05f92c891fd
		}
		else
		{
<<<<<<< HEAD
			if (nread > 0)
			{
			_strcpy(command, line); /* Copy the line to the command buffer. */
			handle_command(command, environ); /* Handle the command. */
			}
				_print(SHELL_PROMPT); /* Print the shell prompt. */
			fflush(stdout); /* Flush the output buffer. */
		/*	free(line);*/ /* Free the memory allocated by getline. */
		/*	line = NULL;*/ /* Reset the pointer to NULL to prevent dangling poi
			signal(SIGINT, handle_sigint);
			_print(SHELL_PROMPT);
			fflush(stdout);
			while ((nread = _getline(&line, &len, stdin)) != -1)
			{
				_strcpy(command, line);
				handle_command(command, environ);
				_print(SHELL_PROMPT);
				fflush(stdout);
				free(line);
				line = NULL;
			}
>>>>>>> c594e3f56a1f4c1324459aa5e163b05f92c891fd
		}
		if (line != NULL)
		free(line);
	}
	return (0);
}
