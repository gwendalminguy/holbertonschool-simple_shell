#include "main.h"

/**
 * main - ...
 *
 * Return: 0
 */
int main(void)
{
	char *line;
	size_t len;
	ssize_t read;
	char *value;
	list_t *path_list = NULL;
	char *arguments[4096];

	value = _getenv("PATH");
	path_list = create_path_list(value);

	while (1)
	{
		if (isatty(STDIN_FILENO) != 0)
		{
			printf("$ ");
		}

		/* Prompting user for input */
		read = getline(&line, &len, stdin);

		if (read < 0)
		{
			break;
		}

		get_arguments(line, arguments);

		process_command(arguments);
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

	while (str != NULL)
	{
		arguments[i] = str;
		str = strtok(NULL, " \n");
		i++;
	}
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
