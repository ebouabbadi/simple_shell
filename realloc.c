#include "shell.h"

/**
 * mYrealloc - function that takes buffxd and increase it's size
 *
 * @old_buffxd: old data of the buffxd
 * @old_size: size of the buffxd before update
 * @new_size: size of the buffxd after
 * Return: buffxd after it's being allocated, NULL in error
 */
void *mYrealloc(void *old_buffxd, size_t old_size, size_t new_size)
{
	unsigned char *buffxd;
	unsigned char *char_buffxd;
	size_t iter;

	buffxd = malloc(sizeof(unsigned char) * (new_size + 1));
	if (!buffxd)
		return (NULL);
	char_buffxd = old_buffxd;
	iter = 0;
	while (char_buffxd && iter < old_size)
	{
		buffxd[iter] = char_buffxd[iter];
		iter++;
	}

	while (iter < new_size)
	{
		buffxd[iter] = 0;
		iter++;
	}
	buffxd[iter] = 0;
	free(old_buffxd);
	return (buffxd);
}
