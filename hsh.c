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
	char *value = NULL;
	list_t *path_list = NULL;
	char *arguments[4096];
	int code = 0, status = 0;

	value = get_env("PATH", env);
	path_list = create_path_list(value);
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
		if (arguments[0][0] != '/' && arguments[0][0] != '.')
		{
			arguments[0] = search_path_list(arguments[0], path_list, &code);
			status = 1;
		}
		code = process_command(arguments, argv, env);
		if (status == 1)
			free(arguments[0]);
		if (code == -1)
			break;
	}
	if (value != NULL)
		free(value);
	free(line);
	free_list(path_list);
	if (code == -1)
		exit(127);
	return (0);
}
