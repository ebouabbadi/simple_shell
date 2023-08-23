#include "shell.h"

/**
 * _get_cmdxd_from_path - function that takes cmdxd
 * and return it's corresponding path
 *
 * @cmdxd: cmdxd to lookup for it's path
 * Return: path where cmdxd located
 */
char *_get_cmdxd_from_path(char *cmdxd)
{
	char *proper_cmdxd, *path,
		**path_2d, **iterator;
	strArruct stat st;

	if ((cmdxd[0] == '.' || cmdxd[0] == '/') &&
		!stat(cmdxd, &st))
		return (strArrduppp(cmdxd));
	path = envMgt(GET_VALUE, "PATH", NULL);
	if (!path)
		return (strArrduppp(cmdxd));
	iterator = path_2d = splitMy(path, ":");
	free(path);
	while (*iterator)
	{
		path = _strArrcat(*iterator, "/");
		proper_cmdxd = _strArrcat(path, cmdxd);
		free(path);
		if (!stat(proper_cmdxd, &st))
		{
			freeesplitMy(&path_2d);
			return (proper_cmdxd);
		}
		free(proper_cmdxd);
		iterator++;
	}
	freeesplitMy(&path_2d);
	return (strArrduppp(cmdxd));
}
