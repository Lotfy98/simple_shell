#include "shell.h"
/**
 * _print - print my output
 * @str: pointer to string
 */
void _print(char *str)
{
	write(STDOUT_FILENO, str, _strlen(str));
}
/**
 * handle_sigint - handling the SIGINT signal in a programming context
 * @sig: signal
 */
void handle_sigint(int sig)
{
	(void)sig;
	_print("\n");
	_print(SHELL_PROMPT);
	fflush(stdout);
}
/**
 * handle_cd - Changes the current working directory.
 * @args: Null-terminated array of arguments for the command.
 * @environ: Null-terminated array of environment variables (unused).
 *
 * Return: Void.
 */
void handle_cd(char **args, char **environ)
{

	(void)environ; /* Unused variable. */

	if (chdir(args[1]) != 0) /*If changing directory fails, print error message*/
	{
		perror("cd failed");
	}
}
/**
 * handle_exit - Exits the shell.
 * @args: Null-terminated array of arguments for the command.
 * @environ: Null-terminated array of environment variables (unused).
 *
 * Return: Void.
 */
void handle_exit(char **args, char **environ)
{
	int status = 0;
	(void)environ;

	if (args[1] != NULL)
		status = _atoi(args[1]);
	exit(status);
}

/**
 * handle_ls - Executes the ls command in a child process.
 * @args: Null-terminated array of arguments for the command.
 * @environ: Null-terminated array of environment variables.
 *
 * Return: Void.
 */
void handle_ls(char **args, char **environ)
{
    pid_t pid;

    pid = fork(); /* Create a child process. */
    if (pid < 0) /* If fork failed, print an error message and return. */
    {
        perror("fork failed");
        return;
    }

    if (pid == 0) /* If this is the child process, execute the ls command. */
    {
        execve("/bin/ls", args, environ);

        /* If execve returns, it must have failed. */
        perror("execve failed");

        exit(1); /* Exit with a failure status. */
    }
    else /* This is the parent process. Wait for the child to finish. */
    {
        wait(NULL);
    }
}
