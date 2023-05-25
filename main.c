#include "shell.h"

/**
 * get_string - get commands
 * @buffer: buffer
 * @delim: delimeter
 * Return: str
 */
<<<<<<< HEAD

=======
>>>>>>> 46355c796c18ca3762513a2c267d7a9db307b62f
char **get_string(char *buffer, char *delim)
{
	char **arrays;
	char *arg;
	int argc = 0;

	arrays = malloc(sizeof(char *) * 1024);
	arg = strtok(buffer, delim);
	while (arg)
	{
		arrays[argc] = arg;
		arg = strtok(NULL, delim);
		argc++;
	}
	arrays[argc] = NULL;
	return (arrays);
}
/* -------- get string ----- */

/**
 * main - main function
 * @ac: arg count
 * @av: arg vector
 * @env: environ
 * Return: int
 */

/**
 * main - main function
 * @ac: arg count
 * @av: arg vector
 * @env: environ
 * Return: int
 */

int main(int ac, char **av, char **env)
{
	size_t buffer_size = 0;
	char **token, *buffer = NULL;
	int status, nread;
	pid_t pid;
	(void) ac;
	(void) av;
	(void) env;

	while (1)
	{
<<<<<<< HEAD
		write(1, "$ ", 2);
=======
		write(1, "> ", 2);
>>>>>>> 46355c796c18ca3762513a2c267d7a9db307b62f
		nread = getline(&buffer, &buffer_size, stdin);
		if (nread == -1)
		{
			write(1, "\n", 1);
			exit(1);
		}
		buffer[nread - 1] = '\0';
<<<<<<< HEAD

=======
>>>>>>> 46355c796c18ca3762513a2c267d7a9db307b62f
		token = get_string(buffer, " \t\n");
		if (strcmp(token[0], "exit") == 0)
			exit(0);

		pid = fork();
		if (pid == 0)
		{
<<<<<<< HEAD
			if (execve(token[0], token, NULL) == -1)
			{
=======
			array = malloc(sizeof(char *) * 1024);
			*array = buffer;
			execve(array[0], array, NULL);

			command = get_path(token[0]);
			if (command)
				execve(command, token, env);
			else
>>>>>>> 46355c796c18ca3762513a2c267d7a9db307b62f
				printf("Command not found\n");
				exit(0);
			}
		}
		else
			wait(&status);
	}
	return (0);
}
/*--------- main --------*/
