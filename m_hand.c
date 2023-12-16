#include "shell.h"

/**
 * free_up - the entry point.
 * Description - function that frees memory based on the specified format.
 * @format: A format string indicating the type of date to free.
 *              'u' for user_input (char *).
 *              't' for string array (char *).
 *              'p' for path list (path_t **).
 * @...: Var arg based on the format.
 */

void free_up(const char *format, ...)
{
	int m;

	va_list a;
	char *ui;

	va_start(a, format);

	m = 0;
	while (format[m] != '\0')
	{
		switch (format[m])
		{
		case 'u':
			ui = va_arg(a, char *);
			safefree(ui);
			break;
		case 't':
			free_string(va_arg(a, char ***));
			break;
		case 'p':
			free_path_list(va_arg(a, path_t **));
			break;
		default:
			break;
		}
		++m;
	}
	va_end(a);
}
