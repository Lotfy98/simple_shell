#include "shell.h"
/**
 * _strlen - function to give the length of a string
 * @s: pointer to a string
 * Return: length of the string
 */
int _strlen(char *s)
{
	int length = 0;

	while (*s != '\0')
	{
		length += 1;
		s++;
	}
	return (length);
}

/**
 * _strcmp - function used to compare two null-terminated strings
 * @s1: pointer to the first string
 * @s2: pointer to the second string
 * Return: 0 on success
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (*s1)
	{
		if (*s1 != *s2)
		{
			i = ((int)*s1 - 48) - ((int)*s2 - 48);
			break;
		}
		s1++;
		s2++;
	}
	return (i);
}

/**
 * _strncmp - used to compare two strings up to specified number of characters
 * @str1: pointer to the first string
 * @str2: pointer to the second string
 * @n: specified number of characters
 * Return: 0 on success
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		else if (str1[i] == '\0')
			return (0);
	}
	return (0);
}
/**
 * _strcpy - used to copy a null-terminated string
 * @dest: pointer to the destination string
 * @src: pointer to the source string
 * Return: pointer to the destination string
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strcat - used to concatenate one string to the end of another
 * @dest: pointer to the destination string
 * @src: pointer to the source string
 * Return: pointer to the destination string
 */
char *_strcat(char *dest, char *src)
{
	int i, y;

	i = _strlen(dest);
	for (y = 0; src[y]; y++)
		dest[i++] = src[y];
	return (dest);
}
