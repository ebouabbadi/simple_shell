#include "shell.h"

/**
 * varEnvm - function
 * that takes key and return it's respective
 * value
 *
 * @env_key: key to retrieve it's value from enviroment
 * variables
 * Return: corresponding value to given key
 */
char *varEnvm(char *env_key)
{
	char *v;
	int n;

	if (_strcmp(env_key, "?"))
	{
		n = statusmt(GET_STATUS, 0);
		return (_itoa(n));
	}
	if (_strcmp(env_key, "$"))
		return (_itoa(getpid()));
	v = envimat(GET_VALUE, env_key, NULL);
	return (v);
}
