#include "shell.h"

/**
 * cd_dot - The Entry Point.
 * Description - Function that changes to the parent directory.
 * @datash: environ - data relevant.
 * Return: .
 */

void cd_dot(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *d, *cpp, *cpsp;

	getcwd(pwd, sizeof(pwd));
	cpp = _strdup(pwd);
	set_env("OLDPWD", cpp, datash);
	d = datash->args[1];
	if (_strcmp(".", d) == 0)
	{
		set_env("PWD", cpp, datash);
		free(cpp);
		return;
	}
	if (_strcmp("/", cpp) == 0)
	{
		free(cpp);
		return;
	}
	cpsp = cpp;
	rev_string(cpsp);
	cpsp = _strtok(cpsp, "/");
	if (cpsp != NULL)
	{
		cpsp = _strtok(NULL, "\0");

		if (cpsp != NULL)
			rev_string(cpsp);
	}
	if (cpsp != NULL)
	{
		chdir(cpsp);
		set_env("PWD", cpsp, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(cpp);
}

/**
 * cd_to - The Entry Point.
 * Description - Function that changes to a directory given
 * by the user.
 * @datash: directories - data relevant.
 * Return: .
 */

void cd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *d, *cpp, *cpd;

	getcwd(pwd, sizeof(pwd));

	d = datash->args[1];
	if (chdir(d) == -1)
	{
		get_error(datash, 2);
		return;
	}

	cpp = _strdup(pwd);
	set_env("OLDPWD", cpp, datash);

	cpd = _strdup(d);
	set_env("PWD", cpd, datash);

	free(cpp);
	free(cpd);

	datash->status = 0;

	chdir(d);
}

/**
 * cd_previous - The Entry Point.
 * Description - Function that changes to the previous director.
 * @datash: environ - data relevant.
 * Return: .
 */

void cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *pp, *po, *cpp, *cpo;

	getcwd(pwd, sizeof(pwd));
	cpp = _strdup(pwd);

	po = _getenv("OLDPWD", datash->_environ);

	if (po == NULL)
		cpo = cpp;
	else
		cpo = _strdup(po);

	set_env("OLDPWD", cpp, datash);

	if (chdir(cpo) == -1)
		set_env("PWD", cpp, datash);
	else
		set_env("PWD", cpo, datash);

	pp = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, pp, _strlen(pp));
	write(STDOUT_FILENO, "\n", 1);

	free(cpp);
	if (po)
		free(cpo);

	datash->status = 0;

	chdir(pp);
}

/**
 * cd_to_home - The Entry Point.
 * Description - Function that changes to home directory.
 * @datash: environ - data relevant.
 * Return: .
 */

void cd_to_home(data_shell *datash)
{
	char *pp, *h;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	pp = _strdup(pwd);

	h = _getenv("HOME", datash->_environ);

	if (h == NULL)
	{
		set_env("OLDPWD", pp, datash);
		free(pp);
		return;
	}

	if (chdir(h) == -1)
	{
		get_error(datash, 2);
		free(pp);
		return;
	}

	set_env("OLDPWD", pp, datash);
	set_env("PWD", h, datash);
	free(pp);
	datash->status = 0;
}
