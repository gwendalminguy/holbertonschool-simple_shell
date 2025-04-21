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

	path_list = create_path_list(env);

	while (1)
	{
		memset(arguments, 0, sizeof(arguments));
		if (isatty(STDIN_FILENO) != 0)
			printf("$ ");

		read = getline(&line, &len, stdin);
		if (read < 0)
			break;

		get_arguments(line, arguments);
		if (arguments[0] == NULL)
			continue;

		if (arguments[0][0] != '/' && arguments[0][0] != '.')
		{
			arguments[0] = search_path_list(arguments[0], path_list);
			status = process_command(arguments, env, argv, status);
			free(arguments[0]);
		}
		else
			status = process_command(arguments, env, argv, status);

		if (status == -1 || status == 127)
			break;
	}

	free(line);
	free_list(path_list);
	exit(status);
}
