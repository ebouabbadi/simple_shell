#include "shell.h"

/**
 * _get_command_from_path - function that takes command
 * and return it's corresponding path
 *
 * @command: command to lookup for it's path
 * Return: path where command located
 */
char *_get_command_from_path(char *command)
{
	char *proper_command, *path,
		**path_2d, **iterator;
	strArruct stat st;

	if ((command[0] == '.' || command[0] == '/') &&
		!stat(command, &st))
		return (strArrduppp(command));
	path = envMgt(GET_VALUE, "PATH", NULL);
	if (!path)
		return (strArrduppp(command));
	iterator = path_2d = splitMy(path, ":");
	free(path);
	while (*iterator)
	{
		path = _strArrcat(*iterator, "/");
		proper_command = _strArrcat(path, command);
		free(path);
		if (!stat(proper_command, &st))
		{
			freeesplitMy(&path_2d);
			return (proper_command);
		}
		free(proper_command);
		iterator++;
	}
	freeesplitMy(&path_2d);
	return (strArrduppp(command));
}
