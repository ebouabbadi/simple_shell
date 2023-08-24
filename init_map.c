#include "shell.h"

/**
 * initMp - initializes a new hash table and returns a pointer to it.
 *
 * Return: a pointer two inititialized map
 */
map_t *initMp(void)
{
	map_t *map = (map_t *)malloc(sizeof(map_t));
	int iterator;

	iterator = 0;
	while (iterator < BACKET_SIZE)
	{
		map->backets[iterator] = NULL;
		iterator++;
	}
	return (map);
}
