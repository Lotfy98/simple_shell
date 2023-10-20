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
		write(1, *environ, _strlen(*environ));
		write(1, "\n", _strlen("\n"));
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
		{"cp", handle_cp}, /* cp command */
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
	int status;

	if (access(cmd, X_OK) == -1)
	{
		write(STDOUT_FILENO, "Command '", 9);
		write(STDOUT_FILENO, cmd, _strlen(cmd));
		write(STDOUT_FILENO, "' does not exist.\n", 18);
		return;
	}
	pid = fork(); /* Create a child process. */
	if (pid < 0) /* If fork failed, print an error message and return. */
	{
		perror("fork failed");
		return;
	}
	else if (pid == 0) /* If this is the child process, execute the command. */
	{
		execve(cmd, args, environ);
		/* If execve returns, it must have failed. */
		perror("execve failed");
		exit(1); /* Exit with a failure status. */
	}
	else
		wait(&status);
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
	char *trimmed_command = trim(command); /* Trim leading and trailing spaces */
	char *cmd_path, *cmd = NULL;
	char **args;
	int i;

	trimmed_command[_strlen(trimmed_command)] = '\0';

	/* Use whitespace as delimiter and continue until a non-NULL command is found */
	while (cmd == NULL && _strlen(trimmed_command) > 0) {
		cmd = _strtok(trimmed_command, " \t\n");
		trimmed_command = trimmed_command + _strlen(cmd) + 1;
	}

	/* Check if cmd is NULL before proceeding */
	if (cmd == NULL) {
		return;
	}

	args = parse_args(cmd);

	commands = getCommand();

	for (i = 0; commands[i].name != NULL; i++) {
		if (_strcmp(cmd, commands[i].name) == 0) {
			commands[i].func(args, environ);
			free_args(args); /* Free the dynamically allocated memory */
			return;
		}
	}

	if (cmd[0] == '/')
		execute_command(cmd, args, environ);
	else {
		cmd_path = _getpath(cmd, environ);
		if (cmd_path == NULL) {
			_print("Command not found: ");
			_print(cmd);
			_print("\n");
			free_args(args); /* Free the dynamically allocated memory */
			return;
		}
		execute_command(cmd_path, args, environ); /* Execute the command with cmd_path */
		free(cmd_path); /* Free cmd_path to prevent memory leaks */
	}

	free_args(args); /* Free the dynamically allocated memory */
}
