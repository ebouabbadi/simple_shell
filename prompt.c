#include "shell.h"

/**
 * ppt - function that asks
 * a user to enter a cmdxd
 *
 * Return: Nothing (void)
 */
void ppt(void)
{
	if (isatty(STDIN_FILENO))
	{
		myFprint(1, "%s> ",
				globalistNodeates(GET_SHELL_NAME, NULL));
	}
}
