#include "main.h"

/**
 * copy_env - copies all environment variables in an array of strings
 * @env: environment variables
 * @environment: destination
 *
 * Return: number of variables
 */
int copy_env(char **env, char **environment)
{
	int i = 0;

	while (env[i] != NULL)
	{
		environment[i] = strdup(env[i]);
		i++;
	}

	return (i);
}

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
	int number = 0;
	char *variable = NULL;
	char *value = NULL;
	char *copy = NULL;
	char *environment[4096];

	memset(environment, 0, sizeof(environment));
	number = copy_env(env, environment);
	len = strlen(name);

	/* Searching for a matching variable */
	while (environment[i] != NULL)
	{
		variable = strtok(environment[i], "=\n");
		value = strtok(NULL, "=\n");

		cmp = strncmp(name, variable, len);

		if (cmp == 0 && value != NULL)
		{
			copy = strdup(value);
			free_env(environment, number);
			return (copy);
		}

		i++;
	}

	free_env(environment, number);

	return (NULL);
}

/**
 * free_env - frees an array of environment variables
 * @env: array of environment variables
 * @number: number of variables
 */
void free_env(char **env, int number)
{
	int i = 0;

	while (i < number)
	{
		if (env[i] != NULL)
		{
			free(env[i]);
			i++;
		}
	}
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
 * @argv: ...
 * @env: environment variables
 *
 * Return: status code
 */

int process_command(char **arguments, char **argv, char **env)
{
	pid_t child_pid;
	int status;
	struct stat st;

	if (stat(arguments[0], &st) != 0)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", argv[0], arguments[0]);
		return (-1);
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		fprintf(stderr, "Error\n");
		exit(-1);
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
