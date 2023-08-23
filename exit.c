#include "shell.h"

/**
 * __exit - function that exit
 * from the program
 *
 * @cmdxd: strArruct that holds data
 * about cmdxd
 * Return: 0 success, otherwise error
 */
int __exit(cmdxd_t *cmdxd)
{
	char **iterator;
	int len;

	iterator = cmdxd->arguments + 1;
	len = stringArr2dlenn(iterator);
	if (len > 0 && !_isdigit(*iterator))
	{
		myFprint(2, "%s: %d: exit: Illegal number: %s\n",
				globalistNodeates(GET_SHELL_NAME, NULL),
				*((int *)globalistNodeates(GET_LINE_NUMBER, NULL)),
				cmdxd->arguments[1]);
		return (2);
	}
	else
	{
		envMgt(CLEAR_ENV, NULL, NULL);
		free(globalistNodeates(GET_LINE, NULL));
		iterator = globalistNodeates(GET_2D, NULL);
		freeesplitMy(&iterator);
		if (!len)
		{
			_free_cmdxd(cmdxd);
			_exit(statusMgt(GET_STATUS, 0));
		}
		len = myAtoi(cmdxd->arguments[1]);
		_free_cmdxd(cmdxd);
		_exit(len);
	}
	return (0);
}
