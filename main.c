#include "shell.h"

char *_getenv(const char *env_var)
{
	extern char **environ;
	int i = 0;
	char *key;

	while (environ[i])
	{
		key = strtok(environ[i], "=");
		if (strcmp(env_var, key) == 0)
			return (strtok(NULL, "\n"));
		i++;
	}
	return (NULL);
}

char *get_path(char *command)
{
	char *path = _getenv("PATH");
	char *token;
	char *command_path;

	token = strtok(path, ":");
	while (token)
	{
		command_path = malloc(strlen(token) + strlen(command) + 2);
		strcpy(command_path, token);
		strcat(command_path, "/");
		strcat(command_path, command);
		if (access(command_path, X_OK) == 0)
			return (command_path);
		free(command_path);
		token = strtok(NULL, ":");
	}
	return (0);
}

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

int main(int ac, char **av, char **env)
{
	size_t buffer_size = 0;
	char **token, **array, *buffer = NULL,  *command;
	int status, nread;
	pid_t pid;
	(void) ac;
	(void) av;

	while (1)
	{
		write (1, "> ", 2);
		nread = getline(&buffer, &buffer_size, stdin);
		if (nread == -1)
		{
			write(1, "\n", 1);
			exit (1);
		}
		buffer[nread - 1] = '\0';
		array = malloc(sizeof(char *) * 1024);
		*array = buffer;
		execve(array[0], array, NULL);

		token = get_string(buffer, " \t\n");
		if (strcmp(token[0], "exit") == 0)
			exit(0);

		
		pid = fork();
		if (pid == 0)
		{
			command = get_path(token[0]);
			if (command)
				execve(command, token, env);
			else
				printf("Command not found\n");
			exit(0);
		}
		else
			wait(&status);
	}
	return (0);
}
