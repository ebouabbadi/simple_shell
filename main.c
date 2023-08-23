#include "shell.h"

/**
 * main - level function
 *
 * @ac: number of passed arguments
 * @av: arguments
 * Return: 0 sucess, otherwise error
 */
int main(int ac, char *av[])
{
	char *line, *no_comment_line;

	(void)ac;
	signal(SIGINT, _handle_sigint);
	envMgt(INIT_ENV, NULL, NULL);
	feedEnvVar(__environ);
	bMgt(SET_BUILTIN, "exit", __exit);
	bMgt(SET_BUILTIN, "env", _env);
	bMgt(SET_BUILTIN, "setenv", _setenv);
	bMgt(SET_BUILTIN, "unsetenv", _unsetenv);
	bMgt(SET_BUILTIN, "cd", _cd);
	globalStates(SET_SHELL_NAME, &av[0]);
	while (true)
	{
		ppt();
		getLinee(&line);
		if (!line)
		{
			free(line);
			break;
		}
		no_comment_line = trimWhiteSpc(line);
		free(line);
		line = no_comment_line;
		no_comment_line = excludeComt(line);
		free(line);
		line = no_comment_line;
		globalStates(SET_LINE, &line);
		globalStates(INCREMENT_LINE_NUMBER, NULL);
		seminHandler(line);
		free(line);
	}
	envMgt(CLEAR_ENV, NULL, NULL);
	return (statusMgt(GET_STATUS, 0));
}
