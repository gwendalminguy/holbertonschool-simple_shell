#include "main.h"

/**
 * main - prompts user for a command and executes it
 * @argc: number of arguments
 * @argv: arguments
 * @env: environment variables
 *
 * Return: 0
 */
int main(int argc __attribute__((unused)),
	 char **argv __attribute__((unused)),
	 char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	char *value = NULL;
	list_t *path_list = NULL;
	char *arguments[4096];
	char *command = NULL;

	value = _getenv("PATH", env);
	path_list = create_path_list(value);

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
		if (arguments[0][0] == '/' || arguments[0][0] == '.')
			command = strdup(arguments[0]);
		else
			command = search_path_list(arguments[0], path_list);
		if (command != NULL)
		{
			arguments[0] = strdup(command);
			process_command(arguments);
			free(arguments[0]);
			free(command);
		}
	}

	free(line);
	free_list(path_list);

	return (0);
}

/**
 * get_arguments - transforms user input in an array of strings
 * @line: user input
 * @arguments: array of strings
 */
void get_arguments(char *line, char **arguments)
{
	int i = 0;
	char *str;

	str = strtok(line, " \n");

	if (str != NULL)
	{
		while (str != NULL)
		{
			arguments[i] = str;
			str = strtok(NULL, " \n");
			i++;
		}
	}
	else
		arguments[0] = NULL;
}

/**
 * process_command - process the given command
 * @arguments: array of strings
 */

void process_command(char **arguments)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		dprintf(STDERR_FILENO, "Error\n");
		exit(1);
	}

	if (child_pid == 0)
	{
		execve(arguments[0], arguments, NULL);
		exit(1);
	}
	else
	{
		wait(&status);
	}
}
