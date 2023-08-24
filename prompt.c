#include "shell.h"

/**
 * pmt - function that asks
 * a user to enter a command
 *
 * Return: Nothing (void)
 */
void pmt(void)
{
	if (isatty(STDIN_FILENO))
	{
		_fprint(1, "%s> ",
				globalStatus(GET_SHELL_NAME, NULL));
	}
}
