#include "shell.h"

/**
 * splitter - 2D ptr to func
 * @str: string arg
 * Return: string
 */

char **splitter(char *str)
{
	char **token = NULL, *tok;
	int i = 0;

	tok = strtok(str, " \t\n");
	while (tok != NULL)
	{
		i++;
		token = realloc(token, i * sizeof(char *));
		if (token == NULL)
		{
			perror("NULL");
			exit(EXIT_FAILURE);
		}
		else
		{
			token[i - 1] = tok;
			tok = strtok(NULL, " \t\n");
		}
	}
	token = realloc(token, (i + 1) * sizeof(char *));
	if (token == NULL)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	return (token);
}

/* -------- splitter ------ */

/**
 * handle_args - handles the args passed to the main
 * Return: 0
 */

int handle_args(void)
{
	char *buffer, **args;
	size_t size = 0;
	int chars = 0, i = 0;

	buffer = NULL;
	chars = getline(&buffer, &size, stdin);
	if (chars == EOF)
	{
		perror("end of file");
		return (1);
	}
	else
	{
		buffer[chars - 1] = '\0';
		printf("%s\n", buffer);
	}
	args = splitter(buffer);
	while (args[i] != NULL)
	{
		printf("Argument %d: %s\n", i, args[i]);
		i++;
	}
	free(buffer);
	free(args);
	return (0);
}

/* -------- handle_ args ------ */
