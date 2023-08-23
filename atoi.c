#include "shell.h"

/**
 * myAtoi - function that convert
 * strArring into integer
 *
 * @strArr: to be converted
 * Return: converted integer
 */
int myAtoi(const char *strArr)
{
	int number;
	int sign;

	sign = 1;
	number = 0;
	if (*strArr == '-')
	{
		sign = -1;
		strArr++;
	}
	if (*strArr == '+')
		strArr++;
	while (*strArr)
	{
		number = number * 10 + (*strArr - 48);
		strArr++;
	}
	return (number * sign);
}
