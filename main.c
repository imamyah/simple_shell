#include "shell.h"

/**
 * main - creates a simple shell
 * @ac: arg count
 * @av: arg vector
 * Return: 0
 */

int main(int ac, char *av[])
{
	char *input, *command, *args[ARGS_SIZE];
	int exit_loop = 0, loops = 0, result;
	(void)ac;
	(void)av;

	if (isatty(STDIN_FILENO) == 1)
	{/*if associated to a terminal*/
		while (exit_loop != 1)
		{/*shell main loop*/
			write(STDOUT_FILENO, "Shell$ ", 7);
			fflush(stdout); /*flush output buffer*/
			input = read_cmd();
			if (input != NULL)
			{
				comments(input);
				splitter(input, args);
				command = args[0];
				if (builtins(args) == 1)
					continue; /*env builtin or cd -> restart loop*/
				result = _fork(args, command);
				loops++;
				if (result != 0)
				{
					error(args, loops);
				}
			}
			free(input);
		}
		free(input);
	}
	return (0);
}
