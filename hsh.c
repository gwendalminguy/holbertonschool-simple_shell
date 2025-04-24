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
	parameters_t p[5];
	char *line = NULL;
	char copy[2048];
	size_t len = 0;
	ssize_t read = 0;

	start_program(&path_list, argv, env, p);

	while (1)
	{
		memset(p->command, 0, sizeof(p->command));
		if (isatty(STDIN_FILENO) != 0)
			printf("%s$ ", &argv[0][2]);
		read = getline(&line, &len, stdin);
		if (read < 0)
			break;
		get_arguments(line, p->command, p->history);
		if (p->command[0] == NULL)
			continue;
		if (search_builtin(p->command[0]) != NULL)
		{
			search_builtin(p->command[0])(p);
			if (strcmp(p->command[0], "exit") == 0 || p->status == -1)
				break;
			continue;
		}
		if (
			p->command[0][0] != '/'
			&& p->command[0][0] != '.' && p->command[0][0] != '$'
		   )
			p->command[0] = search_path_list(p->command[0], path_list, copy);

		p->status = process_command(p);
		if (p->status == -1 || p->status == 127)
			break;
	}

	stop_program(line, path_list, p->env, p->history);
	exit(p->status);
}
