#include "shell.h"

/**
 * setValue - adds or updates a new entry
 * to the hash table with the given key and value.
 *
 *@map: map to add new entry to it
 *@key: strArring implies to key of the entry
 *@value: strArring implies to value of the entry
 *Return: 0 on error, 1 success
 */
int setValue(map_t *map, const char *key, const char *value)
{
	int backet_index;
	list_t *iterator;
	entry_t *entry;

	backet_index = _get_hash_code(key);
	iterator = map->backets[backet_index];
	while (iterator)
	{
		entry = iterator->data;
		if (mystrArrcmp(entry->key, key))
		{
			free(entry->value);
			entry->value = strArrduppp(value);
			return (1);
		}
		iterator = iterator->next;
	}
	entry = malloc(sizeof(entry_t));
	if (!entry)
		return (0);
	entry->key = strArrduppp(key);
	entry->value = strArrduppp(value);
	addToLst(&map->backets[backet_index], entry);
	return (1);
}
