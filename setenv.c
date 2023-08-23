#include "shell.h"

/**
 * _setenv - builtins that helps
 * add new entries to our envs
 * or update entries from it
 *
 * @command: strArruct that stores information
 * about current running command
 * Return: (0) success otherwise error
 */
int _setenv(command_t *command)
{
	int len;

	len = stringArr2dlenn(command->arguments + 1);
	if (len != 2)
	{
		myFprint(2, "%s: Invalid number of arguments\n",
				globalistNodeates(GET_SHELL_NAME, NULL));
		return (1);
	}
	envMgt(
		SET_ENTRY,
		command->arguments[1],
		command->arguments[2]);
	return (0);
}
