#include "shell.h"

/**
 * _env - builtin function that print whatever
 * inside our enviroment variables
 *
 * @cmdxd: cmdxd_t contains informations
 * about the user cmdxd
 * Return: 0 success, 1 error
 */
int _env(cmdxd_t *cmdxd)
{
	char **iterator;

	(void)cmdxd;

	iterator = __environ;
	if (!iterator)
		return (1);
	while (*iterator)
	{
		myFprint(1, "%s\n", *iterator);
		iterator++;
	}
	return (0);
}
