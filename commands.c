#include "main.h"

/**
 * get_env - gets an environment variable
 * @name: name of variable to get
 * @env: environment variable
 *
 * Return: value of the environment variable
 */
char *get_env(const char *name, char **env)
{
	int i = 0, len = 0, cmp = 0;
	char *variable = NULL;
	char *value = NULL;

	len = strlen(name);

	/* Searching for a matching variable */
	while (env[i] != NULL)
	{
		variable = strtok(env[i], "=\n");
		value = strtok(NULL, "=\n");

		cmp = strncmp(name, variable, len);

		if (cmp == 0 && value[0] != '\0')
		{
			return (value);
		}

		i++;
	}

	return (NULL);
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
 * @env: ...
 *
 * Return: ...
 */

int process_command(char **arguments, char **env)
{
	pid_t child_pid;
	int status;
	struct stat st;

	if (stat(arguments[0], &st) != 0)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", arguments[0]);
		return (1);
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		fprintf(stderr, "Error\n");
		exit(1);
	}

	if (child_pid == 0)
	{
		execve(arguments[0], arguments, env);
		exit(0);
	}
	else
	{
		wait(&status);
	}

	return (0);
}
