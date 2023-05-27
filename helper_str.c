#include "shell.h"

/**
 * str_length - length of a string.
 * @string:  string.
 * Return: length of the string.
 */

int str_length(char *string)
{
	int len = 0;

	if (string == NULL)
		return (0);

	while (string[len++] != '\0')
	{
	}
	return (--len);
}
/*-------------*/


/**
 * str_duplicate - duplicates strings
 * @string: String to be duplicated
 * Return: dup str
 */

char *str_duplicate(char *string)
{
	char *res;
	int len, i;

	if (string == NULL)
		return (NULL);

	len = str_length(string) + 1;

	res = malloc(sizeof(char) * len);

	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len ; i++)
	{
		res[i] = string[i];
	}

	return (res);
}
/*-----------------*/


/**
 * str_compare - Compare two strings
 * @string1: String 1
 * @string2: String 2
 * @number: number of characters to be compared, 0 if infinite
 * Return: int
 */

int str_compare(char *string1, char *string2, int number)
{
	int itert;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0) /* infinite longitud */
	{
		if (str_length(string1) != str_length(string2))
			return (0);
		for (itert = 0; string1[itert]; itert++)
		{
			if (string1[itert] != string2[itert])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of chars to be compared */
	{
		for (itert = 0; itert < number ; itert++)
		{
			if (string1[itert] != string2[itert])
			return (0);
		}
		return (1);
	}
}
/*-----------------------------*/


/**
 * str_concat - concatenates two strings.
 * @string1: String 1
 * @string2: String 2
 * Return: array of chars
 */

char *str_concat(char *string1, char *string2)
{
	char *res;
	int len1 = 0, len2 = 0;

	if (string1 == NULL)
		string1 = "";
	len1 = str_length(string1);

	if (string2 == NULL)
		string2 = "";
	len2 = str_length(string2);

	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of string1 */
	for (len1 = 0; string1[len1] != '\0'; len1++)
		res[len1] = string1[len1];
	free(string1);

	/* copy of string2 */
	for (len2 = 0; string2[len2] != '\0'; len2++)
	{
		res[len1] = string2[len2];
		len1++;
	}

	res[len1] = '\0';
	return (res);
}
/*-----------*/

/**
 * str_reverse - reverses a string.
 * @string: pointer to string.
 * Return: void.
 */

void str_reverse(char *string)
{

	int ind = 0, len = str_length(string) - 1;
	char hold;

	while (ind < len)
	{
		hold = string[ind];
		string[ind++] = string[len];
		string[len--] = hold;
	}
}
/*------------------*/
