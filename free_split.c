#include "shell.h"
/**
 * freeesplitMy - function that frees the allocted backets
 *
 * @backets: backets to free
 * Return: void
 */
void freeesplitMy(char ***backets)
{
	char **head;

	head = *backets;
	while (*head)
	{
		free(*head);
		head++;
	}
	free(*backets);
	*backets = NULL;
}
