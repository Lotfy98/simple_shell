#include "shell.h"
/**
 * _strchr - locates a character in a string
 * @s: the string to be searched
 * @c: the character to be located
 *
 * Description: This function takes a string and a character as input.
 * It iterates over the string and checks each
 *character against the input char.
 * If a match is found, it returns a pointer to the
 *first occurrence of the character in the string.
 * If no match is found, it returns NULL.
 *
 * Return: pointer to the first occurrence of the character c in the string s,
 *or NULL if the character is not found
 */
char *_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
/**
 * _strtok - breaks a string into a sequence of zero or more nonempty tokens
 * @str: the string to be tokenized
 * @delimiters: the delimiters to be used for tokenization
 *
 * Description: This function takes a string and a set of delimiters as input.
 * It returns a pointer to the next token in the string,
 *or NULL if there are no more tokens.
 * The function maintains internal state for subsequent calls.
 *
 * Return: pointer to the next token, or NULL if there are no more tokens
 */
char *_strtok(char *str, const char *delimiters)
{
	static char *lastToken;
	char *token;

	if (str != NULL)
		lastToken = str;
	else if (lastToken == NULL || *lastToken == '\0')
		return (NULL);
	while (*lastToken && _strchr(delimiters, *lastToken) != NULL)
		lastToken++;
	if (*lastToken == '\0')
		return (NULL);
	token = lastToken;
	while (*lastToken && _strchr(delimiters, *lastToken) == NULL)
		lastToken++;
	if (*lastToken == '\0')
		lastToken = NULL;
	else
		*lastToken++ = '\0';
	return (token);
}
/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previously allocated
 * @old_size: size in bytes of the allocated space for ptr
 * @new_size: new size in bytes of the new memory block
 *
 * Description: This function takes a pointer to a memory block
 *previously allocated with a call to malloc,
 *the size in bytes of the allocated space for ptr and the new size in
 *bytes of the new memory block.
 * The contents will be copied to the newly allocated space,
 *in the range from the start of ptr up to the minimum of the old
 *and new sizes. If new_size > old_size,
 *the added memory will not be initialized.
 * If new_size is equal to old_size then return ptr.
 * If new_size is 0 and ptr is not NULL, then call free(ptr) and return NULL.
 *
 * Return: pointer to the newly allocated memory, or NULL if it fails
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *newPtr, *oldPtr;
	unsigned int i = 0;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	newPtr = malloc(new_size);
	if (newPtr == NULL)
		return (NULL);
	oldPtr = ptr;
	i = 0;
	if (new_size < old_size)
	{
		while (i < new_size)
		{
			newPtr[i] = oldPtr[i];
			i++;
		}
	}
	else
	{
		while (i < old_size)
		{
			newPtr[i] = oldPtr[i];
			i++;
		}
	}

	free(ptr);
	return (newPtr);
}
/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 *
 * Description: This function takes a string as input.
 * It iterates over the string and checks each character.
 * If the character is a digit, it is converted to an
 *integer and added to the result.
 * If the character is a '-', the sign of the result is flipped.
 * The iteration stops when a non-digit character is encountered after the
 *first digit, or when the end of the string is reached.
 *
 * Return: the converted integer, or 0 if no conversion could be performed
 */
int _atoi(char *s)
{
	unsigned int x = 0;
	int y = 1;

	do {
		if (*s == '-')
			y *= -1;

		else if (*s >= '0' && *s <= '9')
			x = (x * 10) + (*s - '0');

		else if (x > 0)
			break;

	} while (*s++);

	return (x * y);
}
/**
 *_getchar - reads a single character from the standard input
 * Description: This function uses the read system call to read a single
 *character from the standard input (file descriptor STDIN_FILENO).
 * It stores the read character in a local variable and returns it.
 *
 * Return: the character read from the standard input
 */
char _getchar(void)
{
	char c;
	ssize_t bytesRead;
	bytesRead = read(STDIN_FILENO, &c, 1);
	if (bytesRead < 0)
	{
		perror("read");
		return -1;
	}
	else if (bytesRead == 0)
	{
		return EOF;
	}
	else 
	{
	return (c);
	}
}
