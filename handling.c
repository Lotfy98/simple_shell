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
 * @args: Null-terminated array of arguments
 * @environ: The environment variable array.
 */
void handle_cd(char **args, char **environ)
{
	char current_dir[4096];
	(void)environ; /* Unused variable. */

	if (args[1] == NULL)
	{
		/* If no directory argument is provided, change to user's home directory. */
		const char *home_dir = _getenv("HOME", environ);

		if (home_dir == NULL)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", _strlen("cd: HOME not set\n"));
			return;
		}
		if (chdir(home_dir) != 0)
		{
			write(STDERR_FILENO, "cd failed: ", _strlen("cd failed: "));
			perror("");
		}
	}
	else
	{
		/* Change to the specified directory. */
		if (chdir(args[1]) != 0)
		{
			write(STDERR_FILENO, "cd failed: ", strlen("cd failed: "));
			perror("");
		}
	}

	/* Update the environment variable PWD. */

	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
	{
		setenv("PWD", current_dir, 1);
	}
	else
	{
		write(STDERR_FILENO, "getcwd failed: ", _strlen("getcwd failed: "));
		perror("");
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
else
status = 0;

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
	wait(NULL);
	}
