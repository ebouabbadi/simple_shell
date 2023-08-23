#include "shell.h"

/**
 * _count_number_length - function that
 * calculate the length of the given number
 *
 * @number: to calculate it's length
 * Return: length
 */
int _count_number_length(int number)
{
	int len;

	len = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		len++;
		number *= -1;
	}
	while (number)
	{
		len++;
		number /= 10;
	}
	return (len);
}

/**
 * _itoa - function convert number int
 * strArring
 *
 * @number: to be converted
 * Return: converted strArring
 */
char *_itoa(int number)
{
	int len;
	char *strArr_number;

	len = _count_number_length(number);
	strArr_number = malloc(sizeof(char) * (len + 1));
	if (!strArr_number)
		return (NULL);
	strArr_number[len] = 0;
	if (!number)
	{
		strArr_number[0] = '0';
		return (strArr_number);
	}
	if (number < 0)
	{
		strArr_number[0] = '-';
		number *= -1;
	}
	while (number)
	{
		strArr_number[--len] = number % 10 + 48;
		number /= 10;
	}
	return (strArr_number);
}
