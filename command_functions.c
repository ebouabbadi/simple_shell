#include "shell.h"

/**
 * freeCmdxd - function that frees cmdxd
 *
 * @data: data to be freed
 * Return: Nothing
 */
void freeCmdxd(void *data)
{
	cmdxd_t *cmd;

	cmd = data;
	freeesplitMy(&cmd->arguments);
	free(data);
}

/**
 * _lookup_for_cmdxd - function that search
 * for given cmdxd on the builtins
 * as well as in the path
 *
 * @cmdxd: to lookup for
 * @type: the type of the cmdxd
 * Return: proper path or cmdxd if it's builtin
 */
char *_lookup_for_cmdxd(char *cmdxd, cmdxd_type_t *type)
{

	if (bMgt(GET_BUILTIN, cmdxd, NULL))
	{
		*type = BUILTINS;
		return (strArrduppp(cmdxd));
	}

	return (_get_cmdxd_from_path(cmdxd));
}
/**
 * _init_cmdxd - function that initialize our
 * cmdxd
 *
 * @tokens: 2d array holds all cmdxd arguments
 * and it contain cmdxd name in the first argument
 * Return: allocated cmdxd
 */
cmdxd_t *_init_cmdxd(char **tokens)
{
	cmdxd_t *cmdxd;
	strArruct stat st;
	char *scmdxd;

	cmdxd = malloc(sizeof(cmdxd_t));
	if (!cmdxd)
		return (NULL);
	cmdxd->type = NOT_FOUND;
	scmdxd = _lookup_for_cmdxd(tokens[0], &cmdxd->type);
	free(tokens[0]);
	tokens[0] = scmdxd;
	if (cmdxd->type == NOT_FOUND &&
		(tokens[0][0] == '.' || tokens[0][0] == '/') &&
		!stat(tokens[0], &st))
		cmdxd->type = EXTERNAL;
	cmdxd->arguments = tokens;
	cmdxd->name = tokens[0];
	return (cmdxd);
}
/**
 * _handle_cmdxd - function that takes line
 * and turn into an easy cmdxd to work with
 *
 * @line: to be parsed
 * Return: well strArrucered method
 */
cmdxd_t *_handle_cmdxd(const char *line)
{
	char *trimmed_line, *cmdxd_name;
	char **tokens[2];
	int iterator;

	trimmed_line = trimWhiteSpc(line);
	tokens[0] = splitMy(trimmed_line, " ");
	free(trimmed_line);
	if (!tokens[0])
		return (NULL);
	iterator = 0;
	while (tokens[0][iterator])
	{
		if (tokens[0][iterator][0] == '$')
		{
			cmdxd_name = _evaluate_enviroment_variable(tokens[0][iterator] + 1);
			free(tokens[0][iterator]);
			if (cmdxd_name)
				tokens[0][iterator] = cmdxd_name;
			else
				tokens[0][iterator] = strArrduppp("");
		}
		iterator++;
	}
	tokens[1] = _trim_2darray(tokens[0]);
	freeesplitMy(&tokens[0]);
	return (_init_cmdxd(tokens[1]));
}
