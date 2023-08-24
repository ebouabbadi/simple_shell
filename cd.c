#include "shell.h"

/**
 * cdHelps - function helper of cd
 * that takes key and lup
 * in enviromentsble and change
 * directory to it
 *
 * @key: envs keys
 * Return: 0 succeerwise error
 */
int cdHelps(const char *key)
{
	char *s, buffer[200];

	getcwd(buffer, 200);
	s = envimat(GET_VALUE, key, NULL);
	if (chdir(s) == -1)
	{
		free(s);
		return (errno);
	}
	envimat(SET_ENTRY, "OLDPWD", buffer);
	free(s);
	return (0);
}

/**
 * cdHelps2 - function that takes
 * path as parameter and change
 * directory to it
 *
 * @path: path to change directory to it
 * Return: 0 on success ortherwise error
 */
int cdHelps2(const char *path)
{
	char buffer[200];

	getcwd(buffer, 200);
	if (chdir(path) == -1)
	{
		perror(globalStatus(GET_SHELL_NAME, NULL));
		return (errno);
	}
	envimat(SET_ENTRY, "OLDPWD", buffer);
	return (0);
}

/**
 * _cd - builtin function cd
 *  is a function that allows as
 * to navigate through out different
 * folders (directories) in our operating
 * system
 *
 * @cmd: struct the stores information
 * about passed commands
 * Return: (0) success otherwise errors
 */
int _cd(command_t *cmd)
{
	int len;

	len = _str2dlen(cmd->arguments + 1);

	if (len >= 1)
	{
		if (_strcmp("-", cmd->arguments[1]))
			return (cdHelps("OLDPWD"));
		else if (_strcmp("~", cmd->arguments[1]))
			return (cdHelps("HOME"));
		else
			return (cdHelps2(cmd->arguments[1]));
	}
	else if (!len)
		return (cdHelps("HOME"));
	return (0);
}
