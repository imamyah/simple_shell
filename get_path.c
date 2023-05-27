#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - check path to find a program
 * @data: pointer data
 * Return: int
 */

int find_program(data_of_program *data)
{
	int ind = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));
	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);
	directories = tokenize_path(data);
	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (ind = 0; directories[ind]; ind++)
	{
		directories[ind] = str_concat(directories[ind], data->tokens[0]);
		ret_code = check_file(directories[ind]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[ind]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}
/*---------------------------*/


/**
 * tokenize_path - try to tokenize the path in directories
 * @data: ptr to data
 * Return: array of chars
 */

char **tokenize_path(data_of_program *data)
{
	int ind = 0;
	int counter_directories = 2;
	char **tok = NULL;
	char *PATH;

	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}
	PATH = str_duplicate(PATH);
	for (ind = 0; PATH[ind]; ind++)
	{
		if (PATH[ind] == ':')
			counter_directories++;
	}

	tok = malloc(sizeof(char *) * counter_directories);

	ind = 0;
	tok[ind] = str_duplicate(_strtok(PATH, ":"));
	while (tok[ind++])
	{
		tok[ind] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tok);

}
/*------------*/


/**
 * check_file - if exists a file
 * @full_path: the full file name
 * Return: int
 */

int check_file(char *full_path)
{
	struct stat fn;

	if (stat(full_path, &fn) != -1)
	{
		if (S_ISDIR(fn.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exist the file*/
	errno = 127;
	return (127);
}
/*-----------------*/
