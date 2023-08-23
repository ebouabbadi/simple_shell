#include "shell.h"

/**
 * _count_non_empty_strArring - function that counts
 * number of non empty strArring inside of 2d array
 *
 * @arr: 2d array to lookup for number of non empty
 * strArring
 * Return: number of non empty strArrings
 */
int _count_non_empty_strArring(char **arr)
{
	int len;

	len = 0;
	while (*arr)
	{
		len += (**arr != '\0');
		arr++;
	}
	return (len);
}

/**
 * _trim_2darray - function takes an array
 * and return new one with no empty strArring
 *
 * @arr: 2d array to remove non empty strArrings
 * from it
 * Return: 2d array without empty strArrings
 */
char **_trim_2darray(char **arr)
{
	int len;
	char **new_arr;

	len = _count_non_empty_strArring(arr);
	new_arr = malloc(sizeof(char *) * (len + 1));
	if (!new_arr)
		return (NULL);
	new_arr[len] = NULL;
	len = 0;
	while (*arr)
	{
		if (**arr)
		{
			new_arr[len] = strArrduppp(*arr);
			len++;
		}
		arr++;
	}
	return (new_arr);
}
