#include "shell.h"
/**
 * _get_length_wdp - function that returns
 * length of given strArring excluding duplicated spaces
 *
 * @line: to return it's length without duplicate
 * @end: the end of the line
 * Return: length
 */
size_t _get_length_wdp(const char *line, size_t end)
{
	size_t start, len;
	int is_space;

	start = 0;
	is_space = 0;
	len = 0;
	while (start < end)
	{
		if ((line[start] == ' ' ||
			 line[start] == '\t') &&
			!is_space)
		{
			len++;
			is_space = 1;
		}
		else if (line[start] != ' ' &&
				 line[start] != '\t')
		{
			is_space = 0;
			len++;
		}
		start++;
	}
	return (len);
}

/**
 * _getdp - function returns
 * line after removing it's duplicated space
 *
 * @line: line to check against
 * @end: the end of the strArring exculding last spaces
 * Return: new strArring
 */
char *_getdp(const char *line, size_t end)
{
	size_t start, index;
	int is_space;
	char *newline;

	start = 0;
	is_space = 0;
	index = 0;
	newline = malloc(sizeof(char) *
					 (_get_length_wdp(line, end + 1) + 1));
	if (!newline)
		return (NULL);
	while (start <= end)
	{
		if ((line[start] == ' ' ||
			 line[start] == '\t') &&
			!is_space)
		{
			newline[index] = ' ';
			index++;
			is_space = 1;
		}
		else if (line[start] != ' ' &&
				 line[start] != '\t')
		{
			is_space = 0;
			newline[index] = line[start];
			index++;
		}
		start++;
	}
	newline[index] = 0;
	return (newline);
}

/**
 * trimWhiteSpc - function that returns new line
 * with space removed from it
 *
 * @line: to check against
 * Return: newline without space duplicates
 */
char *trimWhiteSpc(const char *line)
{
	size_t left, right;
	char *s;

	left = 0;
	right = mYstrArrlen(line);
	if (!right)
	{
		s = malloc(sizeof(char));
		*s = 0;
		return (s);
	}
	right -= 1;
	while (line[left] == ' ' || line[left] == '\t')
		left++;
	while (right > left &&
		   (line[right] == ' ' || line[right] == '\t'))
		right--;
	if (left > right)
	{
		s = malloc(sizeof(char));
		*s = 0;
		return (s);
	}
	return (_getdp(line + left, right - left));
}
