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
 * struct builtin_s - builtin command
 * @name: name of the command
 * @fptr: function pointer
 */
typedef struct builtin_s
{
	char *name;
	void (*fptr)(char **command,
		     char **env,
		     int *status,
		     char **argv);
} builtin_t;

/* Functions from commands.c */
char *get_env(const char *name, char **env, char *copy);
void get_arguments(char *line, char **arguments);
int get_integer(char *str);
int process_command(char **arguments, char **env, char **argv, int status);

/* Functions from paths.c */
list_t *create_path_list(char **env, char **environment);
char *search_path_list(char *command, list_t *paths, char *copy);
void add_node_list(list_t **head, const char *str);
void print_list(const list_t *head);
void free_list(list_t *head, char **environment);

/* Functions from builtin.c */
void (*search_builtin(char *name))(char **command, char **env, int *status, char **argv);
void builtin_exit(char **command, char **env, int *status, char **argv);
void builtin_cd(char **command, char **env, int *status, char **argv);
void builtin_help(char **command, char **env, int *status, char **argv);

/* Functions from environment.c */
void copy_env(char **env, char **environment);
void free_env(char **env);
void builtin_printenv(char **command, char **env, int *status, char **argv);
void builtin_setenv(char **command, char **env, int *status, char **argv);
void builtin_unsetenv(char **command, char **env, int *status, char **argv);

#endif
