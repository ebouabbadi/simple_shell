#include "shell.h"

/**
 * _strArrcat  - function that takes 2 strArring and
 * combines them
 *
 * @strArr1: first strArring
 * @strArr2: second strArring
 * Return: the combination of first and second strArring
 * NULL on error case
 */
char *_strArrcat(const char *strArr1, const char *strArr2)
{
	size_t len1, len2, iter;
	char *newstrArr;

	len1 = mYstrArrlen(strArr1);
	len2 = mYstrArrlen(strArr2);
	newstrArr = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!newstrArr)
		return (NULL);
	iter = 0;
	while (iter < len1)
	{
		newstrArr[iter] = strArr1[iter];
		iter++;
	}
	while (iter - len1 < len2)
	{
		newstrArr[iter] = strArr2[iter - len1];
		iter++;
	}
	newstrArr[iter] = 0;
	return (newstrArr);
}
