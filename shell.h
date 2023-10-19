#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>

#define MAX_PATH_LENGTH 256
#define MAX_COMMAND_LENGTH 1024
#define SHELL_PROMPT "($) "


void handle_cp(char **args, char **environ);
void _print(char *str);
void handle_sigint(int sig);
void handle_cd(char **arg, char **environ);
void handle_exit(char **arg, char **environ);
void handle_ls(char **arg, char **environ);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strdup(char *str);
int _strlen(char *s);
int _strncmp(const char *str1, const char *str2, size_t n);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char _getchar(FILE *stream);
int _atoi(char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strtok(char *str, const char *delimiters);
char *_strchr(const char *s, int c);
void handle_command(char *command, char **environ);
char *_getpath(char *cmd, char **environ);
char *_getenv(char *name, char **environ);
char *_memcpy(char *dest, char *src, unsigned int n);
int _strcmp(char *s1, char *s2);
char *trim(char *str);
int _isspace(char c);
void execute_command(char *cmd, char **arg, char **environ);
void handle_env(char **args, char **environ);
void handle_cp(char *args[], char **environ);

/**
 * struct Command - Defines a command and its corresponding function
 * @name: Name of the command as a string
 * @func: Function pointer to the command's handler function
 */
typedef struct Command
{
	char *name;
	void (*func)(char **args, char **environ);
} Command;


Command *getCommand();
#endif
