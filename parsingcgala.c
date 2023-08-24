#include "shell.h"

/**
 * check_in - function that check
 * given line against invalid characters
 *
 * @line: to lookup for invalid characters
 * Return: 1 if  invalid character found otherwise 0
 */
int check_in(char *line)
{
	size_t index, iter, iter2;
	char *invChar[] = {
		";;",
		"|||",
		">>>",
		"<<"};

	index = 0;
	while (index < 4)
	{
		iter = 0;
		iter2 = 0;
		while (line[iter2] && invChar[index][iter] &&
			   (invChar[index][iter] == line[iter2] || line[iter2] == ' '))
		{
			if (line[iter2] == ' ')
				iter2++;
			else
			{
				iter2++;
				iter++;
			}
		}
		if (!invChar[index][iter])
			return (1);
		index++;
	}
	return (0);
}

/**
 * _parsing_error_handler - function that takes line
 * and run it against some parsing errors
 *
 * @line: to check against
 * Return: number greater than zero error case or zero if no error occured
 */
int _parsing_error_handler(char *line)
{
	size_t len;

	if (!line || !*line)
		return (0);
	len = _strlen(line);
	if (line[0] == ';' || line[0] == '|' ||
		line[len - 1] == '|' ||
		line[len - 1] == '>' || line[len - 1] == '<')
		return (2);
	len = 0;
	while (line[len])
	{
		if (check_in(line + len))
			return (2);
		len++;
	}
	return (0);
}
