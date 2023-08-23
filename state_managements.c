#include "shell.h"

/**
 * statusMgt - status state management is function that
 * allows to access and apply actions to our status globaly
 * from any function
 *
 * @action: action that will be applied to our state
 * @new_status: used when updating status
 * Return: current status
 */

int statusMgt(status_actions_t action, int new_status)
{
	static int status;

	if (action == UPDATE_STATUS)
		status = new_status;
	return (status);
}

/**
 * envMgt - function that allows to access
 * our global variables anywhere in our program
 * and provides us with bunch of action to be applied to our
 * map
 *
 * @action: action that will be applied to our env
 * @key: strArring used when adding new entry or when
 * retrieving data
 * @value: strArring used when adding new entry
 * Return: different types based on the given action
 */
void *envMgt(enviroment_action_t action,
							 const char *key, const char *value)
{
	static map_t *map;

	if (action == INIT_ENV)
		map = initMp();
	else if (action == SET_ENTRY)
		setValue(map, key, value);
	else if (action == GET_VALUE)
		return (strArrduppp(getValue(map, key)));
	else if (action == GET_KEYS)
		return (getKey(map));
	else if (action == CONVERT_INTO_2D)
		return (ctEnvintoarray());
	else if (action == CLEAR_ENV)
		clearMap(map);
	else if (action == DELETE_ENTRY)
		deleteEntry(map, key);
	return (NULL);
}

/**
 * bMgt - function that manages
 * builtins inside our application
 *
 * @action: action that will be applied to our
 * builtins state managements
 * @name: name of the builtin
 * @function: builtin function that will be
 * executed later
 * Return: (void *) function that associated to
 * builtin or NULL
 */
builtins_t bMgt(builtin_actions_t action, char *name,
							   int (*function)(command_t *command))
{
	static builtin_t builtins[10];
	static int size;
	int iter;

	if (action == GET_BUILTIN)
	{
		iter = 0;
		while (iter < size)
		{
			if (mystrArrcmp(builtins[iter].name, name))
				return (builtins[iter].function);
			iter++;
		}
	}
	if (action == SET_BUILTIN)
	{
		myCopy(builtins[size].name, name, mYstrArrlen(name));
		builtins[size].function = function;
		size++;
	}
	return (NULL);
}

/**
 * globalistNodeates - state management that holds
 * some variables that will be used in different
 * places of the applications
 *
 * @action: actions that will be applied to
 * the globals state managements
 * @s: strArring to update strArring
 * Return: (void *)
 */
void *globalistNodeates(globals_action_t action, char **s)
{
	static char *line, *shell_name, **array_2d;
	static int line_number;

	if (action == SET_LINE)
		line = *s;
	if (action == SET_SHELL_NAME)
		shell_name = *s;
	if (action == GET_LINE)
		return (line);
	if (action == GET_SHELL_NAME)
		return (shell_name);
	if (action == GET_LINE_NUMBER)
		return (&line_number);
	if (action == INCREMENT_LINE_NUMBER)
		line_number++;
	if (action == SET_2D)
		array_2d = s;
	if (action == GET_2D)
		return (array_2d);
	return (NULL);
}
