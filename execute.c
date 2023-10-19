#include "shell.h"
/**
 * handle_env - Prints the environment variables.
 * @args: Null-terminated array of arguments (unused).
 * @environ: Null-terminated array of environment variables.
 *
 * Return: Void.
 */
void handle_env(char **args, char **environ)
{
	(void)args;

	while (*environ != NULL)
	{
		write(1, *environ, strlen(*environ));
		write(1, "\n", 1);
		environ++;
	}
}
/**
 * getCommand - Returns an array of Command structs.
 *
 * Return: An array of Command structs.
 */
Command *getCommand()
{
	/* Define a static array of Command structs. */
	static Command commands[] = {
		{"ls", handle_ls}, /* ls command */
		{"cd", handle_cd}, /* cd command */
		{"exit", handle_exit}, /* exit command */
		{"env", handle_env}, /* env command */
		{NULL, NULL} /* Null-terminated array */
	};
	return (commands); /* Return the array. */
}
/**
 * execute_command - Executes a command in a child process.
 * @cmd: The command to execute.
 * @args: Null-terminated array of arguments for the command.
 * @environ: Null-terminated array of environment variables.
 *
 * Return: Void.
 */
void execute_command(char *cmd, char **args, char **environ)
{
	pid_t pid;
	if (access(cmd, X_OK) == -1) {
		printf("Command '%s' does not exist.\n", cmd);
		return;
	}
	
	pid = fork(); /* Create a child process. */

	if (pid < 0) /* If fork failed, print an error message and return. */
	{
		perror("fork failed");
		return;
	}
	if (pid == 0) /* If this is the child process, execute the command. */
	{
		execve(cmd, args, environ);
		/* If execve returns, it must have failed. */
		perror("execve failed");
		exit(1); /* Exit with a failure status. */
	}
	else /* This is the parent process. Wait for the child to finish. */
		wait(NULL);
}
/**
 * handle_command - Function to handle commands
 * @command: The command to handle
 * @environ: The environment variables
 *
i* This function handles a given command. It trims the command,
 *checks if it's empty,and splits it into cmd and args.
 * It then loops through the commands array to find a match.
 * If a match is found, it executes the associated function.
 * If the cmd starts with '/',
 *it's considered a path to an executable. If not,
 *it searches for the cmd in the system's PATH.
 * If the cmd is not found in the PATH, it prints an error message
 * Otherwise, it executes the command.
 */
void handle_command(char *command, char **environ)
{
	Command *commands;
	char *trimmed_command = trim(command);
	char *cmd_path, *cmd, *arg;
	char *args[64];
	int i;
	trimmed_command[_strlen(trimmed_command)] = '\0';

	if (_strlen(trimmed_command) == 0)
		return;
	cmd = _strtok(trimmed_command, " ");
	args[0] = cmd;
	i = 1;
	while ((arg = _strtok(NULL, " ")) != NULL)
		args[i++] = arg;
	args[i] = NULL;
	commands = getCommand();
	for (i = 0; commands[i].name != NULL; i++)
	{
		if (_strcmp(cmd, commands[i].name) == 0)
		{
			commands[i].func(args, environ);
			return;
		}
	}
	if (cmd[0] == '/')
		execute_command(cmd, args, environ);
	else
	{
		cmd_path = _getpath(cmd, environ);
		if (cmd_path == NULL)
		{
			_print("Command not found: ");
			_print(cmd);
			_print("\n");
			return;
		}
		if (cmd_path != NULL) {
		execute_command(cmd_path, args, environ);
		free(cmd_path);
		}
	}
}
