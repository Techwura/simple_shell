#include "main.h"

/**
 * repeated_char - The Entry Point.
 * Description - counts the repetitions of a character.
 * @input: the input string.
 * @i: the index.
 * Return: the repetitions.
 */

int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - The Entry Point.
 * Description - finds syntax errors.
 * @input: the input string.
 * @i: the index.
 * @last: the last character read.
 * Return: index of error.no errors == 0.
 */

int error_sep_op(char *input, int i, char last)
{
	int c;

	c = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			c = repeated_char(input, 0);
			if (c == 0 || c > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			c = repeated_char(input, 0);
			if (c == 0 || c > 1)
				return (i);
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_char - The Entry Point.
 * Description - finds index of the first character.
 * @input: the input string.
 * @i: the index.
 * Return: 1 if there is an error. Otherwise, 0.
 */

int first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - The Entry Point.
 * Description - prints when a syntax error is found.
 * @datash: the data structure.
 * @input: the input string.
 * @i: index of the error.
 * @bool: control message error.
 * Return: .
 */

void print_syntax_error(data_shell *datash, char *input, int i, int bool)
{
	char *m, *m2, *m3, *error, *c;
	int l;

	if (input[i] == ';')
	{
		if (bool == 0)
			m = (input[i + 1] == ';' ? ";;" : ";");
		else
			m = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		m = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		m = (input[i + 1] == '&' ? "&&" : "&");

	m2 = ": Syntax error: \"";
	m3 = "\" unexpected\n";
	c = aux_itoa(datash->counter);
	l = _strlen(datash->av[0]) + _strlen(c);
	l += _strlen(m) + _strlen(m2) + _strlen(m3) + 2;

	error = malloc(sizeof(char) * (l + 1));
	if (error == 0)
	{
		free(c);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, c);
	_strcat(error, m2);
	_strcat(error, m);
	_strcat(error, m3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, l);
	free(error);
	free(c);
}

/**
 * check_syntax_error - The Entry Point.
 * Description - intermediate function to find and print
 * a syntax error.
 * @datash: the data structure.
 * @input: the input string.
 * Return: 1 if there is an error. Otherwise, 0.
 */

int check_syntax_error(data_shell *datash, char *input)
{
	int b = 0, f = 0, m = 0;

	f = first_char(input, &b);
	if (f == -1)
	{
		print_syntax_error(datash, input, b, 0);
		return (1);
	}

	m = error_sep_op(input + b, 0, *(input + b));
	if (m != 0)
	{
		print_syntax_error(datash, input, b + m, 1);
		return (1);
	}

	return (0);
}
