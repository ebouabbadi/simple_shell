#include "shell.h"

/**
 * fxewline - function that look up for newline or end of the buffxd
 *
 * @buffxd: buffxd to look up in
 * @length: the length of the buffxd
 * Return: number of read character or -1 in case of error
 */
size_t fxewline(char *buffxd, size_t length)
{
	size_t position;

	position = 0;
	while (position < length && buffxd[position] != '\n')
		position++;
	return (position);
}
/**
 * getLinee - function takes address of line to fill with characters
 *
 * @line: address to line that will be filled with characters
 * Return: number of read characters in case of error return -1
 */
ssize_t getLinee(char **line)
{
	static char buffxd[buffxd_SIZE];
	static ssize_t current_position, end_of_buffxd;
	ssize_t old_size, next_newline;

	*line = NULL;
	old_size = 0;
	while (1)
	{
		if (current_position >= end_of_buffxd)
		{
			end_of_buffxd = read(STDIN_FILENO, buffxd, buffxd_SIZE);
			current_position = 0;
			if (end_of_buffxd < 0)
			{
				free(*line);
				*line = NULL;
				return (-1);
			}
			if (end_of_buffxd == 0)
				return (old_size);
		}
		next_newline = fxewline(buffxd + current_position,
										 end_of_buffxd - current_position);
		*line = mYrealloc(*line, old_size, old_size + next_newline);
		if (!*line)
			return (-1);
		myCopy((*line) + old_size, buffxd + current_position, next_newline);
		old_size += next_newline;
		current_position += next_newline;
		if (current_position < end_of_buffxd)
		{
			current_position++;
			return (old_size);
		}
		current_position++;
	}
	return (-1);
}
