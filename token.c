#include "shell.h"

/**
 * _strtok - the entry point.
 * Description - function that splits a string into words.
 * @str: split input string.
 * @delim: the delim.
 * Return: array of words.
 */

char **_strtok(const char *str, char *delim)
{
	char **w;
	int nw, m, j;
	int s = 0, e = 0, i = 0, l;

	if (delim == NULL)
		delim = " \t\n";
	if (str == NULL || *str == '\0')
		return (NULL); /* Handle invalid input */
	nw = countwords(str);
	if (nw == 0)
		return (NULL); /* No words found in the string */
	w = malloc((nw + 1) * sizeof(char *));
	if (w == NULL)
	{
		return (NULL); /* memory allocation failure */
	}
	l = strlen(str);
	for (m = 0; m < l; m++)
	{
		if ((!_strchr(delim, str[m]) && _strchr(delim, str[m + 1])) ||
				(!_strchr(delim, str[m]) && str[m + 1] == '\0'))
		{
			e = m + 1;
			w[i] = copyword(str, s, e);
			if (w[i] == NULL)
			{
				for (j = 0; j < i; ++j)
					safefree(w[j]);
				safefree(w);
				return (NULL);
			}
			i++;
		}
		else if (!_strchr(delim, str[m]) && !_strchr(delim, str[m + 1]))
			continue;
		else
			s = m + 1;
	}
	w[i] = NULL;
	return (w);
}


/**
 * countwords - the entry point.
 * Description - function that counts the number of words in a string.
 * @str: input string.
 * Return: number of words.
 */

int countwords(const char *str)
{
	int w = 0;
	bool iw = false; /* flag to keep track if we are inside a word */
	int m;

	for (m = 0; str[m] != '\0'; ++m)
	{
		if (str[m] == ':' || isspace(str[m]))
		{
			iw = false;
		}
		else if (!iw)
		{
			iw = true;
			w++;
		}
	}
	return (w);
}


/**
 * copyword - the entry point.
 * Description - function that copies a word from a string.
 * @str: input string.
 * @start: word start index.
 * @end: word end index.
 * Return: newly allocated string.
 */

char *copyword(const char *str, int start, int end)
{
	char *w;
	int l = end - start; /* Calc. length of the word */

	w = (char *)malloc((l + 1) * sizeof(char));
	if (w == NULL)
		return (NULL);

	/* Copy chars of the word from input string */
	strncpy(w, str + start, l);
	w[l] = '\0'; /*  Null-terminate word */

	return (w);
}
