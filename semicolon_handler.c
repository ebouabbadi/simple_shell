#include "shell.h"

/**
 * _execution_handler - function that take command
 * and execute it if command is file otherwise
 * persmission and status is been set to (126)
 *
 * @command: command to be executed
 * Return: Nothing
 */
void _execution_handler(command_t *command)
{
	if (access(command->name, F_OK | X_OK) != -1)
		_excute(command);
	else
	{
		myFprint(2, "%s: %d: %s: Permission denied\n",
				(char *)globalistNodeates(GET_SHELL_NAME, NULL),
				*((int *)globalistNodeates(GET_LINE_NUMBER, NULL)),
				command->name);
		statusMgt(UPDATE_STATUS, 126);
	}
}
/**
 * seminHandler - function that splits given
 * line bu semicolon and pass the result to be
 * handled by other functions
 *
 * @line: command line to be parsed and executed
 * Return: 1 on success or 0 signifying error
 */
int seminHandler(const char *line)
{
	char **semi_commands, **iterator;
	command_t *command;
	int argument_length;

	iterator = semi_commands = splitMy(line, ";");
	if (!iterator)
		return (1);
	while (*iterator)
	{
		command = _handle_command(*iterator);
		if (command->type == NOT_FOUND)
		{
			myFprint(2, "%s: %d: %s: not found\n",
					(char *)globalistNodeates(GET_SHELL_NAME, NULL),
					*((int *)globalistNodeates(GET_LINE_NUMBER, NULL)),
					command->name);
			statusMgt(UPDATE_STATUS, 127);
		}
		else if (command->type == EXTERNAL)
			_execution_handler(command);
		else
		{
			globalistNodeates(SET_2D, semi_commands);
			statusMgt(UPDATE_STATUS,
							   bMgt(
								   GET_BUILTIN,
								   command->name, NULL)(command));
		}
		argument_length = stringArr2dlenn(command->arguments);
		envMgt(SET_ENTRY, "_",
							   command->arguments[argument_length - 1]);
		_free_command(command);
		iterator++;
	}
	freeesplitMy(&semi_commands);
	return (0);
}
