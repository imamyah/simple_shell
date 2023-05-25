#include "shell.h"

/**
 * read_cmd - reads the cmd and saves it as string
 * Return: char *input
 */

char *read_cmd(void)
{
	int result;
	char *cmd = NULL;
	size_t size = SIZE;

	/*fgets_result = fgets(input, SIZE, stdin);*/
	result = getline(&cmd, &size, stdin);
	if (result == -1) /*error*/
	{
		if (result == EOF)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("Read command failed ");
			free(cmd);
			exit(EXIT_FAILURE);
		}
	}
	if (spaces(cmd) == 0) /*empty string/spaces*/
	{
		free(cmd);
		cmd = NULL;
	}
	return (cmd);
}
/*------ read_cmd -------*/

/**
 * splitter - splits cmd string into args
 * @input: cmd
 * @args: separated cmds
 * Return: void
 */

void splitter(char *input, char *args[])
{
	int i = 0, j;
	char cp_input[SIZE + 1], *check_tok;
	char **list_toks = NULL;

	list_toks = malloc((SIZE + 1) * sizeof(char *));
	if (list_toks == NULL)
	{
		perror("malloc Failed");
		/*free(list_tokens);i*/
		return;
	}
	/*make copy of input string*/
	strcpy(cp_input, input);
	/*split input string into tokens: args*/
	check_tok = strtok(cp_input, " \n");
	/*check_token = strtok(cp_input, " ");*/
	while (check_tok != NULL && i < SIZE)
	{
		list_toks[i] = check_tok;
		i++;
		check_tok = strtok(NULL, " \n");
	}
	list_toks[i] = NULL; /*last string in array should be NULL*/
	for (j = 0; j < i; j++)
		args[j] = list_toks[j];
	args[j] = NULL;
	free(list_toks);
}
/*--------splitter--------*/

/**
 * _fork - forks parent and child process and exe cmd
 * @args: arguments str
 * @cmd: command
 * Return: int
 */

int _fork(char *args[], char *cmd)
{
	pid_t fork_result;
	char *path = NULL;
	int stat, error = 0;
	(void)cmd;

	path = get_path(args);
	if (path != NULL)
	{
		fork_result = fork();
		if (fork_result == -1) /*error*/
		{
			perror("Fork failed");
			/*exit(EXIT_FAILURE);*/
		}
		else if (fork_result == 0) /* child process*/
		{
			stat = execve(path, args, environ); /*exe cmd*/
			if (stat == -1)
				error = 1;
			/*perror("execve failed");*/ /*if exe fails*/
			/*exit(EXIT_FAILURE);*/
		} /*child*/
		else /*parent*/
			wait(&stat);
	}
	free(path);
	return (error);
}
/*------- fork -------*/

/**
 * nstr - truns a num to str
 * @nr: number
 * @str: string
 * Return: void
 */

void nstr(int nr, char *str)
{
	int i, j;
	char c;

	for (i = 0; nr != 0; i++)
	{
		str[i] = '0' + (nr % 10);
		nr = nr / 10;
	}
	for (j = 0; j < i / 2; j++)
	{
		c = str[j];
		str[j] = str[i - j - 1];
		str[i - j - 1] = c;
	}
	str[i] = '\0';

}
/*------ num to str -----*/

/**
 * comments - removes comments
 * @input: input
 * Return: void
 */

void comments(char *input)
{
	size_t i;
	int yes = -1;

	for (i = 0; i < strlen(input); i++)
	{ /*check for comment #*/
		if (input[i] == '#')
		{
			yes = i;
			break;
		}
	}
	if (yes != -1)
	{ /*comment found*/
		input[yes] = '\0';
	} /*terminate string at #*/
}
/*------ comments----*/
