#include "main.h"

/**
 * search_builtin - searches for a builtin command
 * @name: name of the command
 *
 * Return: function pointer
 */
void (*search_builtin(char *name))(char **command, char **env, int *status, char **argv)
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
 * @argv: ...
 */
void builtin_exit(char **command, char **env, int *status, char **argv)
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
			fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", argv[0],  command[1]);
			*status = 2;
		}
	}
}

/**
 * builtin_cd - changes current working directory
 * @command: command to process
 * @env: environment variables
 * @status: exit status
 * @argv: ...
 */
void builtin_cd(char **command, char **env, int *status, char **argv)
{
	char current[1024], previous[1024], home[1024];
	char *old_path = NULL, *new_path = NULL;
	int code = -1, size = 0;

	memset(home, 0, sizeof(home));
	memset(previous, 0, sizeof(previous));
	get_env("HOME", env, home);
	get_env("OLDPWD", env, previous);
	old_path = strdup(getcwd(current, 1024));
	if (command[1] == NULL)
	{
		if (home[0] != '\0')
			new_path = strdup(home);
	}
	else if (strcmp(command[1], "-") == 0)
	{
		if (previous[0] != '\0')
			new_path = strdup(previous);
	}
	else if (command[1][0] == '/')
		new_path = strdup(command[1]);
	else
	{
		size = 2 + strlen(old_path) + strlen(command[1]);
		new_path = malloc(size);
		sprintf(new_path, "%s/%s", old_path, command[1]);
	}
	if (new_path != NULL)
	{
		code = chdir(new_path);
		if (code == 0)
		{
			command[1] = "OLDPWD";
			command[2] = old_path;
			builtin_setenv(command, env, status, argv);
			command[1] = "PWD";
			command[2] = new_path;
			builtin_setenv(command, env, status, argv);
		}
		else
			fprintf(stderr, "./%s: 1: cd: can't cd to %s\n", argv[0], command[1]);
		free(new_path);
	}
	*status = 0;
	free(old_path);
}

/**
 * builtin_help - prints help for any builtin command
 * @command: command to process
 * @env: environment variable
 * @status: exit status
 * @argv: ...
 */
void builtin_help(char **command, char **env, int *status, char **argv)
{
	(void)command;
	(void)env;
	(void)status;
	(void)argv;

	printf("Upcoming feature\n");
}
