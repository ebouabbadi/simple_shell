#include "shell.h"

/**
 * __exit - function that exit
 * from the program
 *
 * @command: struct that holds data
 * about command
 * Return: 0 success, otherwise error
 */
int __exit(command_t *command)
{
	char **iterator;
	int len;

	iterator = command->arguments + 1;
	len = _str2dlen(iterator);
	if (len > 0 && !_isdigit(*iterator))
	{
		_fprint(2, "%s: %d: exit: Illegal number: %s\n",
				globalStatus(GET_SHELL_NAME, NULL),
				*((int *)globalStatus(GET_LINE_NUMBER, NULL)),
				command->arguments[1]);
		return (2);
	}
	else
	{
		envimat(CLEAR_ENV, NULL, NULL);
		free(globalStatus(GET_LINE, NULL));
		iterator = globalStatus(GET_2D, NULL);
		_free_split(&iterator);
		if (!len)
		{
			freeCmd(command);
			_exit(statusmt(GET_STATUS, 0));
		}
		len = _atoi(command->arguments[1]);
		freeCmd(command);
		_exit(len);
	}
	return (0);
}
