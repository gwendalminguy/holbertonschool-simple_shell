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
	char *old_path = NULL;
	char *new_path = NULL;
	int code = 0, size = 0;

	old_path = strdup(getcwd(current, 1024));

	if (command[1] == NULL)
		new_path = strdup(get_env("HOME", env, current));
	else if (strcmp(command[1], "-") == 0)
		new_path = strdup(get_env("OLDPWD", env, current));
	else if (command[1][0] != '/')
	{
		size = 2 +strlen(old_path) + strlen(command[1]);
		new_path = malloc(size);

		strcpy(new_path, old_path);
		strcat(new_path, "/");
		strcat(new_path, command[1]);
	}
	else
		new_path = strdup(command[1]);

	code = chdir(new_path);

	if (code == 0)
	{
		command[1] = "OLDPWD";
		command[2] = old_path;
		builtin_setenv(command, env, status);

		command[1] = "PWD";
		command[2] = new_path;
		builtin_setenv(command, env, status);

		*status = 0;
	}
	else
	{
		fprintf(stderr, "hsh: cd: no such directory\n");
		*status = 99;
	}

	free(old_path);
	free(new_path);
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
