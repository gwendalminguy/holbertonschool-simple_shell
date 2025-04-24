#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * struct list_s - singly linked list
 * @str: string
 * @len: length of the string
 * @next: pointer to next node
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

/**
 * struct parameters_s - parameters for builtin commands
 * @command: command to process
 * @env: environment variables
 * @status: exit status
 * @argv: arguments of the program
 * @history: history of commands
 */
typedef struct parameters_s
{
	char *command[4096];
	char *env[4096];
	int status;
	char **argv;
	char *history[4096];
} parameters_t;

/**
 * struct builtin_s - builtin command
 * @name: name of the command
 * @fptr: function pointer
 */
typedef struct builtin_s
{
	char *name;
	void (*fptr)(parameters_t *p);
} builtin_t;

/* Functions from commands.c */
char *get_env(const char *name, char **env, char *copy);
void get_arguments(char *line, char **arguments);
int get_integer(char *str);
int process_command(char **arguments, char **env, char **argv, int status);

/* Functions from paths.c */
list_t *create_path_list(char **env, char **env_copy);
char *search_path_list(char *command, list_t *paths, char *copy);
void add_node_list(list_t **head, const char *str);
void print_list(const list_t *head);
void free_list(list_t *head, char **environment);

/* Functions from builtin.c */
void (*search_builtin(char *name))(parameters_t *p);
void builtin_exit(parameters_t *p);
void builtin_cd(parameters_t *p);
void builtin_help(parameters_t *p);

/* Functions from environment.c */
void copy_env(char **env, char **env_copy);
void free_env(char **env);
void builtin_printenv(parameters_t *p);
void builtin_setenv(parameters_t *p);
void builtin_unsetenv(parameters_t *p);

#endif
