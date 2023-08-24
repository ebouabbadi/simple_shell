#include "shell.h"

/**
 * exclct - remove comment from
 * line
 *
 * @line: full line that user entered
 * Return: new_line without comment
 */
char *exclct(const char *line)
{
	int comment_position;

	comment_position = positionGet(line);
	return (stlinstttt(line, 0, comment_position));
}
