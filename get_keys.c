#include "shell.h"

/**
 * getKey - retrieves a linked list of all the keys in the hash table.
 *
 *@map: map to retrieve
 * Return: list of keys
 */
list_t    *getKey(const map_t *map)
{
	list_t    *list, *iterator;
	entry_t  *entry;
	int      iter;

	list = NULL;
	iter = 0;
	while (iter < BACKET_SIZE)
	{
		iterator = map->backets[iter];
		while (iterator)
		{
			entry = iterator->data;
			addToLst(&list, strArrduppp(entry->key));
			iterator = iterator->next;
		}
		iter++;
	}
	return (list);
}
