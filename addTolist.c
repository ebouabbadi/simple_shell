#include "shell.h"

/**
 * addTolist - Add new node.
 * @lNode: Ptr to ptr of h list.
 * @data: Ptr  to be stored.
 * Return: Ptr to newlynode.
 */
list_t *addTolist(list_t **lNode, void *data)
{
	list_t *nextNode = (list_t *)malloc(sizeof(list_t));
	list_t *go;

	if (nextNode == NULL)
	{
		return (NULL);
	}

	nextNode->data = data;
	nextNode->next = NULL;

	if (*lNode == NULL)
	{
		*lNode = nextNode;
	}
	else
	{
		go = *lNode;
		while (go->next != NULL)
		{
			go = go->next;
		}
		go->next = nextNode;
	}

	return (nextNode);
}
