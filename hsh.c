#include "main.h"

/**
 * main - prompts user for a command and executes it
 * @argc: number of arguments
 * @argv: arguments
 * @env: environment variables
 *
 * Return: 0
 */
int main(int argc __attribute__((unused)), char **argv, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	list_t *path_list = NULL;
	char *arguments[4096];
	int status = 0;
	int i = 0;

	builtin_t builtin[] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{NULL, NULL}
	};

	
	path_list = create_path_list(env);
	
	while (1)
	{
		status = 0;
		memset(arguments, 0, sizeof(arguments));
		if (isatty(STDIN_FILENO) != 0)
			printf("$ ");

		read = getline(&line, &len, stdin);
		if (read < 0)
			break;
		get_arguments(line, arguments);
		if (arguments[0] == NULL)
			continue;
		i = 0;
		while (builtin[i].name)
		{
			if (strcmp(arguments[0], builtin[i].name) == 0)
			{
				builtin[i].func(env);
				break;
			}
			i++;
		}
		if (builtin[i].name != NULL)
		{
			continue;
		}
		
		if (arguments[0][0] != '/' && arguments[0][0] != '.')
		{
			arguments[0] = search_path_list(arguments[0], path_list);
			status = process_command(arguments, env, argv);
			free(arguments[0]);
		}
		else
			status = process_command(arguments, env, argv);

		if (status != 0)
			break;
	}

	free(line);
	free_list(path_list);
	exit(status);
}
