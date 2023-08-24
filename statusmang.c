#include "shell.h"

/**
 * statusmt - state management is function that
 * allows to access and applyour status globaly
 * from any function
 *
 * @action: action that will be applied to our state
 * @new_status: used whenting status
 * Return: current status
 */

int statusmt(status_actions_t action, int new_status)
{
	static int status;

	if (action == UPDATE_STATUS)
		status = new_status;
	return (status);
}

/**
 * envimat - function that allows to access
 * our global variables anywhere in our program
 * and provides be applied to our
 * map
 *
 * @act: act that will be applied to our env
 * @key: string useng new entry or when
 * retrieving data
 * @value: string used when adding new entry
 * Return: different ased on the given act
 */
void *envimat(enviroment_action_t act,
			  const char *key, const char *value)
{
	static map_t *map;

	if (act == INIT_ENV)
		map = initMp();
	else if (act == SET_ENTRY)
		valueSet(map, key, value);
	else if (act == GET_VALUE)
		return (_strdup(_get_value(map, key)));
	else if (act == GET_KEYS)
		return (keyGetGen(map));
	else if (act == CONVERT_INTO_2D)
		return (convert2darry());
	else if (act == CLEAR_ENV)
		clearMp(map);
	else if (act == DELETE_ENTRY)
		deleteEntry(map, key);
	return (NULL);
}

/**
 * bMt - function that manages
 * builtins inside our application
 *
 * @act: act that will bplied to our
 * builtins state managements
 * @name: name of the builtin
 * @function: builtin funct that will be
 * executed later
 * Return: (void *) funcassociated to
 * builtin or NULL
 */
builtins_t bMt(builtin_actions_t act, char *name,
			   int (*function)(command_t *command))
{
	static builtin_t builtins[10];
	static int size;
	int iter;

	if (act == GET_BUILTIN)
	{
		iter = 0;
		while (iter < size)
		{
			if (_strcmp(builtins[iter].name, name))
				return (builtins[iter].function);
			iter++;
		}
	}
	if (act == SET_BUILTIN)
	{
		_copy(builtins[size].name, name, _strlen(name));
		builtins[size].function = function;
		size++;
	}
	return (NULL);
}

/**
 * globalStatus - state mament that holds
 * some variables that will used in different
 * places of the applications
 *
 * @act: actions that we applied to
 * the globals state mements
 * @s: string to update string
 * Return: (void *)
 */
void *globalStatus(globals_action_t act, char **s)
{
	static char *line, *shell_name, **array_2d;
	static int line_number;

	if (act == SET_LINE)
		line = *s;
	if (act == SET_SHELL_NAME)
		shell_name = *s;
	if (act == GET_LINE)
		return (line);
	if (act == GET_SHELL_NAME)
		return (shell_name);
	if (act == GET_LINE_NUMBER)
		return (&line_number);
	if (act == INCREMENT_LINE_NUMBER)
		line_number++;
	if (act == SET_2D)
		array_2d = s;
	if (act == GET_2D)
		return (array_2d);
	return (NULL);
}
