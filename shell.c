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
    char command[MAX_COMMAND_LENGTH]; /* Command buffer. */
    char *line = NULL; /* Line buffer. */
    size_t len = 0; /* Length of the line. */
    ssize_t nread; /* Number of characters read. */
    char *token;
    (void)argc; /* Unused variable. */
    (void)argv; /* Unused variable. */

    if (!isatty(STDIN_FILENO))
    { /* If input is not from a terminal... */
        /* Read lines until EOF. */
        while ((nread = _getline(&line, &len, stdin)) != -1)
        {
            if (nread == 0)
                break;

            /* Split the input into individual commands*/
            token = strtok(line, "\n");
            while (token != NULL)
            {
                strcpy(command, token); /* Copy the line. */
                handle_command(command, environ); /* Handle the command. */
                token = strtok(NULL, "\n");
            }

            free(line); /* Free the memory allocated by getline. */
            line = NULL; /* Prevent dangling pointers. */
            break; /* Exit the loop after executing the command. */
        }
    }
    else
    { /* If input is from a terminal... */
        signal(SIGINT, handle_sigint); /* Handle SIGINT signal (Ctrl+C). */
        printf("Shell Prompt: "); /* Print the shell prompt. */
        fflush(stdout); /* Flush the output buffer. */
        /* Read lines until EOF. */
        while ((nread = _getline(&line, &len, stdin)) != -1)
        {
            /* Split the input into individual commands*/
            token = strtok(line, "\n");
            while (token != NULL)
            {
                strcpy(command, token); /* Copy the line to the command buffer. */
                handle_command(command, environ); /* Handle the command. */
                printf("Shell Prompt: "); /* Print the shell prompt. */
                fflush(stdout); /* Flush the output buffer. */
                token = strtok(NULL, "\n");
            }

            free(line); /* Free the memory allocated by getline. */
            line = NULL; /* Reset the pointer to NULL to prevent dangling pointers. */
        }
    }
    free(line); /* Free any remaining memory at the end of the program. */
    return (0); /* Return success status. */
}
