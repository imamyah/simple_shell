#include "shell.h"

/**
 * error - writes errors
 * @args: arguments
 * @loops: loops executed
 * Return: void
 */

void error(char *args[], int loops)
{
	char *prog = NULL;
	char buff[SIZE], pid[50], prefix[7] = "/proc/",
		loops_str[50];
	int file, rd;

	sprintf(pid, "%d", getpid());
	strcat(prefix, pid);
	strcat(prefix, "/cmdline");
	file = open(prefix, O_RDONLY);
	if (file != -1)
	{
		rd = read(file, buff, sizeof(buff));
		if (rd != -1)
		{
			buff[rd] = '\0';
			prog = malloc(rd + 1);
			strncpy(prog, buff, rd);
			prog[rd] = '\0';
		}
		close(file);
	}
	sprintf(loops_str, "%d", loops);
	write(STDOUT_FILENO, prog, strlen(prog));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, loops_str, strlen(loops_str));
	write(STDOUT_FILENO, ": ", 2);

	if (args[0] != NULL)
		perror(args[0]);
	free(prog);
}
/*----- error ------*/

/**
 * get_path - gets the path of a cmd
 * @args: arguments
 * Return: char str
 */

char *get_path(char *args[])
{
	char *result = NULL;
	char *command = args[0];
	char *path, *cpy_path, *directory;

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
		{
			result = strdup((char *) command);
			return (result);
		}
	}
	else
	{
		path = getenv("PATH");
		cpy_path = strdup(path);
		directory = strtok(cpy_path, ":");
		while (directory != NULL)
		{
			result = malloc(strlen(directory) + strlen(command) + 2);
			if (result == NULL)
			{
				free(result);
				return (NULL);
			}
			strcpy(result, directory);
			strcat(result, "/");
			strcat(result, (char *) command);
			if (access(result, X_OK) == 0)
			{
				free(cpy_path);
				return (result);
			}
			free(result);
			directory = strtok(NULL, ":");
		}
		free(cpy_path);
	}
	return (NULL);
}
/*------ get path -----*/


/**
 * spaces - checks if the command is just spaces
 * @input: input string
 * Return: int (1 = found chars, 0 = just spaces)
 */

int spaces(char *input)
{
	int i;
	int not = 0;

	for (i = 0; input[i] != '\n'; i++)
	{
		if (input[i] != ' ' && input[i] != '\t')
		not = 1;
	}
	return (not);
}
/*------ spaces ----*/
