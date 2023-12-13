#include "main.h"

/**
 * _strcat - The Entry Point.
 * Description - concatenate two strings.
 * @dest: char pointer the dest of the copied string.
 * @src: const char pointer the source of string.
 * Return: dest.
 */

char *_strcat(char *dest, const char *src)
{
	int m;
	int n;

	for (m = 0; dest[m] != '\0'; m++)
		;

	for (n = 0; src[n] != '\0'; n++)
	{
		dest[m] = src[n];
		m++;
	}

	dest[m] = '\0';
	return (dest);
}
/**
 * *_strcpy - The Entry Point.
 * Description - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied string.
 * @src: Type char pointer the source of string.
 * Return: dest.
 */

char *_strcpy(char *dest, char *src)
{

	size_t b;

	for (b = 0; src[b] != '\0'; b++)
	{
		dest[b] = src[b];
	}
	dest[b] = '\0';

	return (dest);
}

/**
 * _strcmp - The Entry Point.
 * Description - Function that compares two strings.
 * @s1: type string compared.
 * @s2: type string compared.
 * Return: Always 0 on success.
 */

int _strcmp(char *s1, char *s2)
{
	int a;

	for (a = 0; s1[a] == s2[a] && s1[a]; a++)
		;

	if (s1[a] > s2[a])
		return (1);
	if (s1[a] < s2[a])
		return (-1);
	return (0);
}

/**
 * _strchr - The Entry Point.
 * Description - locates a char in a string.
 * @s: the string.
 * @c: the char.
 * Return: pointer to the 1st occurrence of the char c.
 */

char *_strchr(char *s, char c)
{
	unsigned int m = 0;

	for (; *(s + m) != '\0'; m++)
		if (*(s + m) == c)
			return (s + m);
	if (*(s + m) == c)
		return (s + m);
	return ('\0');
}

/**
 * _strspn - The Entry Point.
 * Description - gets the length of a prefix substring.
 * @s: the initial segment.
 * @accept: the accepted bytes.
 * Return: the number of accepted bytes.
 */

int _strspn(char *s, char *accept)
{
	int m, n, bool;

	for (m = 0; *(s + m) != '\0'; m++)
	{
		bool = 1;
		for (n = 0; *(accept + n) != '\0'; n++)
		{
			if (*(s + m) == *(accept + n))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (m);
}
