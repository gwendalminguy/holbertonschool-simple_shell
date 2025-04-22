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
	list_t *path_list = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	char *command[4096];
	char *environment[4096];
	int status = 0;
	char copy[2048];

	memset(environment, 0, sizeof(environment));
	path_list = create_path_list(env, environment);

	while (1)
	{
		memset(command, 0, sizeof(command));
		if (isatty(STDIN_FILENO) != 0)
			printf("%s$ ", &argv[0][2]);
		read = getline(&line, &len, stdin);
		if (read < 0)
			break;
		get_arguments(line, command);
		if (command[0] == NULL)
			continue;
		if (search_builtin(command[0]) != NULL)
		{
			search_builtin(command[0])(command, environment, &status, argv);
			if (strcmp(command[0], "exit") == 0)
				break;
			continue;
		}
		if (command[0][0] != '/' && command[0][0] != '.' && command[0][0] != '$')
			command[0] = search_path_list(command[0], path_list, copy);

		status = process_command(command, env, argv, status);
		if (status == -1 || status == 127)
			break;
	}
	free(line);
	free_list(path_list, environment);
	exit(status);
}
