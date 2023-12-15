#include "shell.h"

/**
 * is_cmd - the entry point.
 * Description - determines if a file is an executable command.
 * @info: the info struct.
 * @path: path to the file.
 * Return: Always 1 if true, otherwise 0.
 */

int is_cmd(info_t *info, char *path)
{
	struct stat st;
	(void)info;

	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - the entry point.
 * Description - duplicates characters.
 * @pathstr: the PATH string.
 * @start: beginning index.
 * @stop: stopping index.
 * Return: pointer to new buffer.
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int m = 0, n = 0;

	for (n = 0, m = start; m < stop; m++)
		if (pathstr[m] != ':')
			buf[n++] = pathstr[m];
	buf[n] = 0;
	return (buf);
}

/**
 * find_path - the entry point.
 * Description - finds this cmd in the PATH string.
 * @info: info struct.
 * @pathstr: PATH string.
 * @cmd: cmd to find.
 * Return: full path of cmd if found or NULL.
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int m = 0, cp = 0;
	char *p;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[m] || pathstr[m] == ':')
		{
			p = dup_chars(pathstr, cp, m);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (is_cmd(info, p))
				return (p);
			if (!pathstr[m])
				break;
			cp = m;
		}
		m++;
	}
	return (NULL);
}
