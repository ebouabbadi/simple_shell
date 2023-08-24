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
	envimat(INIT_ENV, NULL, NULL);
	feedEnv(__environ);
	bMt(SET_BUILTIN, "exit", __exit);
	bMt(SET_BUILTIN, "env", _env);
	bMt(SET_BUILTIN, "setenv", _setenv);
	bMt(SET_BUILTIN, "unsetenv", _unsetenv);
	bMt(SET_BUILTIN, "cd", _cd);
	globalStatus(SET_SHELL_NAME, &av[0]);
	while (1)
	{
		pmt();
		myGetline(&line);
		if (!line)
		{
			free(line);
			break;
		}
		no_comment_line = trimspace(line);
		free(line);
		line = no_comment_line;
		no_comment_line = exclct(line);
		free(line);
		line = no_comment_line;
		globalStatus(SET_LINE, &line);
		globalStatus(INCREMENT_LINE_NUMBER, NULL);
		semichr(line);
		free(line);
	}
	envimat(CLEAR_ENV, NULL, NULL);
	return (statusmt(GET_STATUS, 0));
}
