#include "shell.h"

/**
 * addToLst - Add new node.
 * @listNode: Ptr to ptr of head of list.
 * @data: Ptr  to be stored.
 * Return: Ptr to newly added node.
 */
list_t *add_to_list(list_t **listNode, void *data)
{
	list_t *new_node = (list_t *)malloc(sizeof(list_t));
	list_t *current;

	if (new_node == NULL)
	{
		return (NULL);
	}

	new_node->data = data;
	new_node->next = NULL;

	if (*listNode == NULL)
	{
		*listNode = new_node;
	}
	else
	{
		current = *listNode;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}

	return (new_node);
}
