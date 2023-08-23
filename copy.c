#include "shell.h"
/**
 * myCopy - function that copy data into dest
 *
 * @dest: buffxd in which the data will be copied
 * @src: buffxd source of the characters
 * @size: length of data that will be copied into line
 * Return: dest
 */
char *myCopy(char *dest, const char *src, size_t size)
{
	size_t iter;

	iter = 0;
	while (iter < size)
	{
		dest[iter] = src[iter];
		iter++;
	}
	dest[iter] = 0;
	return (dest);
}
