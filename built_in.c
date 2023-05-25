#include "shell.h"

/**
 * builtins - handles builtin functions
 * @args: input arguments
 * Return: int
 */

int builtins(char *args[])
{
	int check = 0, status, i;
	char *env, *parts[] = {"USER", "LANGUAGE", "SESSION",
		 "COMPIZ_CONFIG_PROFILE", "SHLVL", "HOME", "C_IS", "DESKTOP_SESSION",
		 "LOGNAME", "TERM", "PATH", "DISPLAY", "NULL"};

	if (strcmp(args[0], "exit") == 0)
	{
		if (args[1] != NULL)
		{
			status = atoi(args[1]);
		}
		else
		{
			status = EXIT_SUCCESS;
		}
		exit(status);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; parts[i] != NULL; i++)
		{
			env = getenv(parts[i]);
			if (env != NULL)
			{
				write(STDOUT_FILENO, parts[i], strlen(parts[i]));
				write(STDOUT_FILENO, "=", 1);
				write(STDOUT_FILENO, env, strlen(env));
				write(STDOUT_FILENO, "\n", 1);
			}
		}
		check = 1;
	}
	return (check);
}
/*------ builtins -----*/

/**
 * cd - change directory builtin
 * @args: input arguments
 * Return: void
 */

void cd(char *args[])
{
	char *home, *prev, *out, *change;
	char current[SIZE];
	int result;

	home = getenv("HOME");
	prev = getenv("PWD");

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
		change = home;
	else if (strcmp(args[1], "-") == 0)
		change = prev;
	else
		change = args[1];

	if (change == NULL)
	{
		return;
	}
	result = chdir(change); /*change directory*/
	if (result != 0)
	{
		return;
	}
	out = getcwd(current, sizeof(current));
	if (out != NULL)
		setenv("PWD", current, 1);
}
/*------ cd ------ */
