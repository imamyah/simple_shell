#include "shell.h"

/**
 * inicialize_data - init struct to info of the program
 * @data: pointer to  data
 * @argv: arg vector
 * @env: environ
 * @argc: arg count
 * Return: void
 */

void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int ind = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[ind]; ind++)
		{
			data->env[ind] = str_duplicate(env[ind]);
		}
	}
	data->env[ind] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (ind = 0; ind < 20; ind++)
	{
		data->alias_list[ind] = NULL;
	}
}
/*----------------------------*/


/**
 * sisifo - infinite loop that shows the prompt
 * @prompt: prompt
 * @data: ptr to data
 * return: void
 */

void sisifo(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* if a text is given to prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
/*-------------------------*/


/**
 * handle_ctrl_c - ctrl c
 * @UNUSED:unused
 * Return: void
 */

void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}
/*--------------*/
