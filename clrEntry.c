#include "shell.h"

/**
 * clearEntryy - frees the memory hash table.
 *
 * @data :  entry data
 *
 * Return: nothing
 */
void clearEntryy(void *data)
{
	entry_t *entry;

	entry = data;
	free(entry->key);
	free(entry->value);
	free(data);
}
