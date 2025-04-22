#include "main.h"

/**
 * search_builtin - searches for a builtin command
 * @name: name of the command
 *
 * Return: function pointer
 */
void (*search_builtin(char *name))(char **command, char **env, int *status)
{
	int i = 0;

	builtin_t builtin[] = {
		{"exit", builtin_exit},
		{"env", builtin_printenv},
		{"printenv", builtin_printenv},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{"cd", builtin_cd},
		{"help", builtin_help},
		{NULL, NULL}
	};

	while (builtin[i].name)
	{
		if (strcmp(name, builtin[i].name) == 0)
			break;
		i++;
	}

	return (builtin[i].fptr);
}
/**
 * builtin_exit - sets an exit status
 * @command: command to process
 * @env: environnement variables
 * @status: exit status
 */
void builtin_exit(char **command, char **env, int *status)
{
	int n = 0;
	(void)env;

	if (command[1] != NULL)
	{
		n = get_integer(command[1]);

		if (n >= 0)
			*status = n;
		else
		{
			fprintf(stderr, "hsh: 1: exit: Illegal number: %s\n", command[1]);
			*status = 2;
		}
	}
}

/**
 * builtin_cd - changes current working directory
 * @command: command to process
 * @env: environment variables
 * @status: exit status
 */
void builtin_cd(char **command, char **env, int *status)
{
	char current[1024];
	char *path = NULL;
	int code = 0;

	if (command[1] == NULL)
		path = get_env("HOME", env, current);
	else
	{
		path = getcwd(current, 1024);
		strcat(path, "/");
		strcat(path, command[1]);
	}
	
	code = chdir(path);

	if (code == 0)
	{
		command[1] = "PWD";
		command[2] = path;

		builtin_setenv(command, env, status);
		*status = 0;
	}
	else
	{
		fprintf(stderr, "hsh: cd: no such directory\n");
		*status = 99;
	}
}

/**
 * builtin_help - prints help for any builtin command
 * @command: command to process
 * @env: environment variable
 * @status: exit status
 */
void builtin_help(char **command, char **env, int *status)
{
	(void)command;
	(void)env;
	(void)status;

	printf("Upcoming feature\n");
}
