#include "shell.h"

/**
 * _excute - function that excute cmdxds
 * that's not part of builtins
 *
 * @cmdxd: cmdxd to be executed
 * Return: Nothing(void)
 */
void _excute(cmdxd_t *cmdxd)
{
	int pid, status, err;

	pid = fork();
	if (pid < 0)
	{
		perror((char *)globalistNodeates(GET_SHELL_NAME, NULL));
		statusMgt(UPDATE_STATUS, 1);
		return;
	}
	if (!pid)
	{
		execve(cmdxd->name, cmdxd->arguments, __environ);
		err = errno;
		if (errno == EACCES)
		{
			myFprint(2, "%s: %d: %s: Permission denied\n",
					 (char *)globalistNodeates(GET_SHELL_NAME, NULL),
					 *((int *)globalistNodeates(GET_LINE_NUMBER, NULL)),
					 cmdxd->name);
			err = 126;
		}
		else
			perror(globalistNodeates(GET_SHELL_NAME, NULL));
		freeCmdxd(cmdxd);
		free(globalistNodeates(GET_LINE, NULL));
		envMgt(CLEAR_ENV, NULL, NULL);
		_exit(err);
	}
	else
	{
		waitpid(pid, &status, 0);
		statusMgt(UPDATE_STATUS, WEXITSTATUS(status));
	}
}
