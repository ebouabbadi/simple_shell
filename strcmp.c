#include "shell.h"

/**
 * mystrArrcmp - function checks  wether given strArrings
 * are identical or not
 *
 * @strArr1: first strArring to check against
 * @strArr2: second strArring to check against
 *
 * Return: 1 success case, 0 error case
 */
int mystrArrcmp(const char *strArr1, const char *strArr2)
{
	if (!strArr1 || !strArr2)
		return (0);
	while (*strArr1 && *strArr2 && *strArr1 == *strArr2)
	{
		strArr1++;
		strArr2++;
	}
	if (!*strArr1 && !*strArr2)
		return (1);
	return (0);
}
