#include "shell.h"

/**
 * clearMap - frees the memory allocated for an entry in the hash table.
 *
 *@map: map to be freed
 * Return: nothing
 */
void clearMap(map_t *map)
{
	int iterator;

	iterator = 0;
	while (iterator < BACKET_SIZE)
	{
		free_list(map->backets[iterator], clearEntryy);
		iterator++;
	}
	free(map);
}
