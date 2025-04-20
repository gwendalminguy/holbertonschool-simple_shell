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
	int code = 0, status = 0;

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
		if (arguments[0][0] != '/' && arguments[0][0] != '.')
		{
			arguments[0] = search_path_list(arguments[0], path_list);
			status = 1;
		}
		code = process_command(arguments, env, argv);
		if (status == 1)
			free(arguments[0]);
		if (code != 0)
			break;
	}
	free(line);
	free_list(path_list);
	if (code == 127)
		exit(127);
	else if (code == -1)
		exit(-1);
	return (0);
}
