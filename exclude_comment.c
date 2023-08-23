#include "shell.h"

/**
 * excludeComt - remove comment from
 * line
 *
 * @line: full line that user entered
 * Return: new_line without comment
 */
char *excludeComt(const char *line)
{
	int comment_position;

	comment_position = getCcpt(line);
	return (strArrSliceer(line, 0, comment_position));
}
