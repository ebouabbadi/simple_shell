#include "shell.h"

/**
 * _handle_sigint - function that
 * will be called when control-c(SIGINT)
 * triggred
 *
 * @sig: Integer signifying the signal number
 * Return: void
 */
void _handle_sigint(int sig)
{
	(void)sig;
	fflush(stdin);
	if (isatty(STDIN_FILENO))
	{
		myFprint(1, "\n%s> ",
				 globalistNodeates(GET_SHELL_NAME, NULL));
	}
}
