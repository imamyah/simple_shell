#include "shell.h"


/**
 * tokenize - separate the string using a designed delimiter
 * @data: a pointer to data
 * Return: void
 */

void tokenize(data_of_program *data)
{
	char *delim = " \t";
	int k, j, count = 2, len;

	len = str_length(data->input_line);
	if (len)
	{
		if (data->input_line[len - 1] == '\n')
			data->input_line[len - 1] = '\0';
	}

	for (k = 0; data->input_line[k]; k++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (data->input_line[k] == delim[j])
				count++;
		}
	}

	data->tokens = malloc(count * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	k = 0;
	data->tokens[k] = str_duplicate(_strtok(data->input_line, delim));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[k++])
	{
		data->tokens[k] = str_duplicate(_strtok(NULL, delim));
	}
}
/*------------------------*/


/**
 * _strtok - string to token
 * @line: command line
 * @delim: delimeter
 * Return: char
*/

char *_strtok(char *line, char *delim)
{
	int ind;
	static char *str;
	char *copystr;

	if (line != NULL)
	{
		str = line;
	}
	for (; *str != '\0'; str++)
	{
		for (ind = 0; delim[ind] != '\0'; ind++)
		{
			if (*str == delim[ind])
				break;
		}
		if (delim[ind] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (ind = 0; delim[ind] != '\0'; ind++)
		{
			if (*str == delim[ind])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
/*--------------------*/
