#include "shell.h"

/**
 * _setenv - builtins that helps
 * add new entries to our envs
 * or update entries from it
 *
 * @cmdxd: strArruct that stores information
 * about current running cmdxd
 * Return: (0) success otherwise error
 */
int _setenv(cmdxd_t *cmdxd)
{
	int len;

	len = stringArr2dlenn(cmdxd->arguments + 1);
	if (len != 2)
	{
		myFprint(2, "%s: Invalid number of arguments\n",
				globalistNodeates(GET_SHELL_NAME, NULL));
		return (1);
	}
	envMgt(
		SET_ENTRY,
		cmdxd->arguments[1],
		cmdxd->arguments[2]);
	return (0);
}
