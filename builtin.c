#include "main.h"

/**
 * search_builtin - searches for a builtin command
 * @name: name of the command
 *
 * Return: function pointer
 */
void (*search_builtin(char *name))(parameters_t *p)
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
		{"history", builtin_history},
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
 * @p: parameters of the builtin command
 */
void builtin_exit(parameters_t *p)
{
	int n = 0;

	if (p->command[1] != NULL)
	{
		n = get_integer(p->command[1]);

		if (n >= 0)
			p->status = n;
		else
		{
			fprintf(stderr, "%s: 1: exit:", p->argv[0]);
			fprintf(stderr, " Illegal number: %s\n", p->command[1]);
			p->status = 2;
		}
	}
}

/**
 * builtin_cd - changes current working directory
 * @p: parameters of the builtin command
 */
void builtin_cd(parameters_t *p)
{
	char current[1024], previous[1024] = {0}, home[1024] = {0};
	char *old_path = NULL, *new_path = NULL;
	int code = 1, size = 0;

	get_env("HOME", p->env, home);
	get_env("OLDPWD", p->env, previous);
	old_path = strdup(getcwd(current, 1024));

	if (p->command[1] == NULL)
	{
		if (home[0] != '\0')
			new_path = strdup(home);
	}
	else if (!strcmp(p->command[1], "-") && previous[0] != '\0')
		new_path = strdup(previous);
	else if (p->command[1][0] == '/')
		new_path = strdup(p->command[1]);
	else if (p->command[1][0] != '-' && p->command[1][0] != '/')
	{
		size = 2 + strlen(old_path) + strlen(p->command[1]);
		new_path = malloc(size);
		sprintf(new_path, "%s/%s", old_path, p->command[1]);
	}

	/* Changing directory */
	if (new_path != NULL)
		code = chdir(new_path);

	/* Updating OLDPWD and PWD */
	if (code == 0)
	{
		p->command[1] = "OLDPWD";
		p->command[2] = old_path;
		builtin_setenv(p);
		p->command[1] = "PWD";
		p->command[2] = new_path;
		builtin_setenv(p);
	}
	else if (code == -1)
		fprintf(stderr, "%s: 1: cd: can't cd to %s\n", p->argv[0], p->command[1]);
	free(new_path);
	free(old_path);
	p->status = 0;
}

/**
 * builtin_help - prints the help for any builtin command
 * @p: parameters of the builtin command
 */
void builtin_help(parameters_t *p)
{
	if (p->command[1] == NULL || !strcmp(p->command[1], "help"))
	{
		printf("\nhelp: help [BUILT-IN]\n\n");
		printf("\tPrints the help for the command BUILT-IN:\n");
		printf("\texit | env | setenv | unsetenv | cd | help\n\n");
	}
	else if (!strcmp(p->command[1], "exit"))
	{
		printf("\nexit: exit [STATUS]\n\n");
		printf("\tExits the shell with the code STATUS if specified,\n");
		printf("\tor with the exit status of the previous command otherwise.\n\n");
	}
	else if (!strcmp(p->command[1], "env") || !strcmp(p->command[1], "printenv"))
	{
		printf("\nenv: env\n\n");
		printf("\tPrints all environement variables.\n\n");
	}
	else if (!strcmp(p->command[1], "setenv"))
	{
		printf("\nsetenv: setenv VARIABLE VALUE\n\n");
		printf("\tAdds VARIABLE to the environment and initializes it to VALUE,\n");
		printf("\tor updates its value to VALUE if it alreday exists.\n\n");
	}
	else if (!strcmp(p->command[1], "unsetenv"))
	{
		printf("\nunsetenv: unsetenv VARIABLE\n\n");
		printf("\tRemoves VARIABLE from the environment if it exists.\n\n");
	}
	else if (!strcmp(p->command[1], "cd"))
	{
		printf("\ncd: cd [DIRECTORY]\n\n");
		printf("\tChanges current directory to [DIRECTORY] if specified,\n");
		printf("\tor to the HOME directory otherwise.\n\n");
	}
	else if (!strcmp(p->command[1], "history"))
	{
		printf("\nhistory: history\n\n");
		printf("\tPrints the history of all commands.\n");
	}

	p->status = 0;
}

/**
 * builtin_history - prints the history of all commands
 * @p: parameters of the builtin command
 */
void builtin_history(parameters_t *p)
{
	int i = 0;

	while (i < 4096 && p->history[i] != NULL)
	{
		printf("[%i] %s", i, p->history[i]);
		i++;
	}

	p->status = 0;
}
