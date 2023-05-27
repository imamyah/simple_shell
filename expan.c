#include "shell.h"

/**
 * expand_variables - func that expand variables
 * @data: ptr to data
 * Return: void
 */
void expand_variables(data_of_program *data)
{
	int k, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (k = 0; line[k]; k++)
		if (line[k] == '#')
			line[k--] = '\0';
		else if (line[k] == '$' && line[k + 1] == '?')
		{
			line[k] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + k + 2);
		}
		else if (line[k] == '$' && line[k + 1] == '$')
		{
			line[k] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + k + 2);
		}
		else if (line[k] == '$' && (line[k + 1] == ' ' || line[k + 1] == '\0'))
			continue;
		else if (line[k] == '$')
		{
			for (j = 1; line[k + j] && line[k + j] != ' '; j++)
				expansion[j - 1] = line[k + j];
			temp = env_get_key(expansion, data);
			line[k] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + k + j);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}
/*------------------------------*/

/**
 * expand_alias - func expands aliases
 * @data: a ptr data
 * Return: void
 */

void expand_alias(data_of_program *data)
{
	int k, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (k = 0; line[k]; k++)
	{
		for (j = 0; line[k + j] && line[k + j] != ' '; j++)
			expansion[j] = line[k + j];
		expansion[j] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + k + j);
			line[k] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}
/*---------------------------*/

/**
 * buffer_add - add string at end of the buffer
 * @buffer: buffer
 * @str_to_add: string toadd
 * Return: void
 */

int buffer_add(char *buffer, char *str_to_add)
{
	int len, ind;

	len = str_length(buffer);
	for (ind = 0; str_to_add[ind]; ind++)
	{
		buffer[len + ind] = str_to_add[ind];
	}
	buffer[len + ind] = '\0';
	return (len + ind);
}
/*-----------------------*/
