#include "shell.h"

/**
 * long_to_string - converts a number to a string.
 * @number: number to be converten in an string.
 * @string: buffer to save the number as string.
 * @base: base to convert number
 * Return: void.
 */

void long_to_string(long number, char *string, int base)
{
	int i = 0, inNegative = 0;
	long cociente = number;
	char letters[] = {"0123456789abcdef"};

	if (cociente == 0)
		string[i++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (cociente)
	{
		if (cociente < 0)
			string[i++] = letters[-(cociente % base)];
		else
			string[i++] = letters[cociente % base];
		cociente /= base;
	}
	if (inNegative)
		string[i++] = '-';

	string[i] = '\0';
	str_reverse(string);
}
/*-------------------*/

/**
 * _atoi - convert a string to an integer.
 *
 * @s: pointer to str origen.
 * Return: int of string or 0.
 */

int _atoi(char *s)
{
	int sign = 1;
	unsigned int num = 0;
	/*1- analisys sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{
		num = (num * 10) + (*s - '0');
		s++;
	}
	return (num * sign);
}
/*-----------------*/


/**
 * count_characters - count the coincidences of character in string.
 * @string: pointer to str origen.
 * @character: string with  chars to be counted
 * Return: int
 */
int count_characters(char *string, char *character)
{
	int ind = 0, count = 0;

	for (; string[ind]; ind++)
	{
		if (string[ind] == character[0])
			count++;
	}
	return (count);
}
/*---------------------*/
