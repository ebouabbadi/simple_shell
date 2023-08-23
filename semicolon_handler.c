#include "shell.h"

/**
 * _execution_handler - function that take cmdxd
 * and execute it if cmdxd is file otherwise
 * persmission and status is been set to (126)
 *
 * @cmdxd: cmdxd to be executed
 * Return: Nothing
 */
void _execution_handler(cmdxd_t *cmdxd)
{
	if (access(cmdxd->name, F_OK | X_OK) != -1)
		_excute(cmdxd);
	else
	{
		myFprint(2, "%s: %d: %s: Permission denied\n",
				(char *)globalistNodeates(GET_SHELL_NAME, NULL),
				*((int *)globalistNodeates(GET_LINE_NUMBER, NULL)),
				cmdxd->name);
		statusMgt(UPDATE_STATUS, 126);
	}
}
/**
 * seminHandler - function that splits given
 * line bu semicolon and pass the result to be
 * handled by other functions
 *
 * @line: cmdxd line to be parsed and executed
 * Return: 1 on success or 0 signifying error
 */
int seminHandler(const char *line)
{
	char **semi_cmdxds, **iterator;
	cmdxd_t *cmdxd;
	int argument_length;

	iterator = semi_cmdxds = splitMy(line, ";");
	if (!iterator)
		return (1);
	while (*iterator)
	{
		cmdxd = _handle_cmdxd(*iterator);
		if (cmdxd->type == NOT_FOUND)
		{
			myFprint(2, "%s: %d: %s: not found\n",
					(char *)globalistNodeates(GET_SHELL_NAME, NULL),
					*((int *)globalistNodeates(GET_LINE_NUMBER, NULL)),
					cmdxd->name);
			statusMgt(UPDATE_STATUS, 127);
		}
		else if (cmdxd->type == EXTERNAL)
			_execution_handler(cmdxd);
		else
		{
			globalistNodeates(SET_2D, semi_cmdxds);
			statusMgt(UPDATE_STATUS,
							   bMgt(
								   GET_BUILTIN,
								   cmdxd->name, NULL)(cmdxd));
		}
		argument_length = stringArr2dlenn(cmdxd->arguments);
		envMgt(SET_ENTRY, "_",
							   cmdxd->arguments[argument_length - 1]);
		_free_cmdxd(cmdxd);
		iterator++;
	}
	freeesplitMy(&semi_cmdxds);
	return (0);
}
