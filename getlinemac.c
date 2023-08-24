#include "shell.h"

/**
 * pathFromCmd - function  takes cmd
 * and return it's corresponding path
 *
 * @cmd: cmd to lookup for it's path
 * Return: path where  located
 */
char *pathFromCmd(char *cmd)
{
	char *lagala, *path,
		**path_2d, **iterator;
	struct stat st;

	if ((cmd[0] == '.' || cmd[0] == '/') &&
		!stat(cmd, &st))
		return (_strdup(cmd));
	path = envimat(GET_VALUE, "PATH", NULL);
	if (!path)
		return (_strdup(cmd));
	iterator = path_2d = _split(path, ":");
	free(path);
	while (*iterator)
	{
		path = _strcat(*iterator, "/");
		lagala = _strcat(path, cmd);
		free(path);
		if (!stat(lagala, &st))
		{
			_free_split(&path_2d);
			return (lagala);
		}
		free(lagala);
		iterator++;
	}
	_free_split(&path_2d);
	return (_strdup(cmd));
}
