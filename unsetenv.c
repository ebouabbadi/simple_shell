#include "shell.h"

/**
 * _unsetenv - function unset one entry from enviroment
 * variable
 *
 * @command: command that contains information about
 * entry that will be delete such as key of the entry
 * Return: status code
 */
int _unsetenv(command_t *command)
{
	int len;

	len = stringArr2dlenn(command->arguments);
	if (len != 2)
	{
		myFprint(2, "%s: Invalid number of arguments\n",
				globalistNodeates(GET_SHELL_NAME, NULL));
		return (1);
	}
	envMgt(DELETE_ENTRY, command->arguments[1], NULL);
	return (0);
}
