#include "shell.h"
/**
 * mYstrArrlen - function that calculate the length of given strArring
 *
 * @s: strArring (characters)
 * Return: number of characters
 */
size_t mYstrArrlen(const char *s)
{
	size_t len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}
