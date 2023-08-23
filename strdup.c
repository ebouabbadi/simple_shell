#include "shell.h"

/**
* strArrduppp - function that takes a strArring and duplicates
* it and return new pointer of duplicated strArring
*
* @strArr: strArring to be duplicated
* Return: new char pointer to the new strArring
*/
char   *strArrduppp(const char *strArr)
{
	char *new_strArr;
	size_t  len, iterator;

	len = mYstrArrlen(strArr);
	new_strArr = malloc(sizeof(char) * (len + 1));
	if (!new_strArr)
		return (NULL);
	new_strArr[len] = 0;
	iterator = 0;
	while (iterator < len)
	{
		new_strArr[iterator] = strArr[iterator];
		iterator++;
	}
	return (new_strArr);
}
