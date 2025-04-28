#include "main.h"

/**
 * get_env - gets an environment variable
 * @name: name of variable to get
 * @env: environment variable
 * @copy: buffer for the value
 *
 * Return: copy of the value of the environment variable
 */
char *get_env(const char *name, char **env, char *copy)
{
	int i = 0, cmp = 0;
	char *variable = NULL;
	char *value = NULL;
	char *environment[4096];

	memset(environment, 0, sizeof(environment));
	copy_env(env, environment);

	/* Searching for a matching variable */
	while (environment[i] != NULL)
	{
		variable = strtok(environment[i], "=\n");
		value = strtok(NULL, "=\n");

		cmp = strcmp(name, variable);

		if (cmp == 0 && value != NULL)
		{
			/* Copying and freeing */
			strcpy(copy, value);
			free_array(environment);
			return (copy);
		}

		i++;
	}

	free_array(environment);

	return (NULL);
}

/**
 * copy_env - copies all environment variables in an array of strings
 * @env: environment variables
 * @env_copy: destination
 */
void copy_env(char **env, char **env_copy)
{
	int i = 0;

	while (env[i] != NULL)
	{
		env_copy[i] = strdup(env[i]);
		i++;
	}
}

/**
 * builtin_printenv - prints all environment variables
 * @p: parameters of the builtin command
 */
void builtin_printenv(parameters_t *p)
{
	int i = 0;

	while (p->env[i] != NULL)
	{
		printf("%s\n", p->env[i]);
		i++;
	}

	p->status = 0;
}

/**
 * builtin_setenv - adds or updates an environment variable
 * @p: parameters of the builtin command
 */
void builtin_setenv(parameters_t *p)
{
	int i = 0, m = 0, n = 0;
	int size = 0;

	if (p->command[1] != NULL && p->command[2] != NULL)
	{
		m = strlen(p->command[1]);
		n = strlen(p->command[2]);

		while (p->env[i] != NULL)
		{
			/* Freeing variable if it already exists */
			if (strncmp(p->command[1], p->env[i], m) == 0 && p->env[i][m] == '=')
			{
				free(p->env[i]);
				break;
			}

			i++;
		}

		size = m + n;

		/* Allocating memory for the new variable */
		p->env[i] = malloc(size + 2);

		if (p->env[i] == NULL)
		{
			fprintf(stderr, "%s: setenv: malloc failed\n", p->argv[0]);
			p->status = 1;
		}
		else
		{
			memset(p->env[i], 0, size);
			sprintf(p->env[i], "%s=%s", p->command[1], p->command[2]);
			p->status = 0;
		}
	}
	else
	{
		fprintf(stderr, "%s: setenv: missing argument\n", p->argv[0]);
		p->status = 2;
	}
}

/**
 * builtin_unsetenv - removes an environment variable
 * @p: parameters of the builtin commmand
 */
void builtin_unsetenv(parameters_t *p)
{
	int i = 0, n = 0;

	if (p->command[1] != NULL)
	{
		n = strlen(p->command[1]);
		
		/* Searching for the variable to remove */
		while (p->env[i] != NULL)
		{
			if (strncmp(p->command[1], p->env[i], n) == 0 && p->env[i][n] == '=')
				break;
			i++;
		}
		if (p->env[i] == NULL)
		{
			fprintf(stderr, "%s: unsetenv: invalid argument %s\n", p->argv[0], p->command[1]);
			p->status = 2;
		}
		else
		{
			/* Shifting all variables */
			while (p->env[i] != NULL)
			{
				free(p->env[i]);
				if (p->env[i + 1] != NULL)
				{
					p->env[i] = malloc(1 + strlen(p->env[i + 1]));
					if (p->env[i] == NULL)
					{
						fprintf(stderr, "%s: unsetenv: malloc failed\n", p->argv[0]);
						p->status = 1;
						break;
					}
					strcpy(p->env[i], p->env[i + 1]);
				}
				else
				{
					p->env[i] = NULL;
					p->status = 0;
				}
				i++;
			}
		}
	}
	else
	{
		fprintf(stderr, "%s: unsetenv: missing argument\n", p->argv[0]);
		p->status = 2;
	}
}
