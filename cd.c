#include "shell.h"

/**
 * cdHelper - function helper of cd
 * that takes key and look it up
 * in enviroments variable and change
 * directory to it
 *
 * @key: envs keys
 * Return: 0 success otherwise error
 */
int cdHelper(const char *key)
{
	char *s, buffxd[200];

	getcwd(buffxd, 200);
	s = envMgt(GET_VALUE, key, NULL);
	if (chdir(s) == -1)
	{
		free(s);
		return (errno);
	}
	envMgt(SET_ENTRY, "OLDPWD", buffxd);
	free(s);
	return (0);
}

/**
 * cdHelper2 - function that takes
 * path as parameter and change
 * directory to it
 *
 * @path: path to change directory to it
 * Return: 0 on success ortherwise error
 */
int cdHelper2(const char *path)
{
	char buffxd[200];

	getcwd(buffxd, 200);
	if (chdir(path) == -1)
	{
		perror(globalistNodeates(GET_SHELL_NAME, NULL));
		return (errno);
	}
	envMgt(SET_ENTRY, "OLDPWD", buffxd);
	return (0);
}

/**
 * myCd - builtin function cd
 *  is a function that allows as
 * to navigate through
 * folders (directories) in our operating
 * system
 *
 * @cmdxd: strArruct
 * about passed cmd
 * Return: (0) success otherwise errors
 */
int myCd(cmdxd_t *cmdxd)
{
	int len;

	len = stringArr2dlenn(cmdxd->arguments + 1);

	if (len >= 1)
	{
		if (mystrArrcmp("-", cmdxd->arguments[1]))
		{
			return (cdHelper("OLDPWD"));
		}
		else if (mystrArrcmp("~", cmdxd->arguments[1]))
		{
			return (cdHelper("HOME"));
		}
		else
		{
			return (cdHelper2(cmdxd->arguments[1]));
		}
	}
	else if (!len)
		return (cdHelper("HOME"));
	return (0);
}
