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

int copy_env(char **env, char **environment);
char *get_env(const char *name, char **env);
void free_env(char **env, int number);
void get_arguments(char *line, char **arguments);
int process_command(char **arguments, char **argv, char **env);

list_t *create_path_list(char *value);
char *search_path_list(char *command, list_t *paths, int *code);
void add_node_list(list_t **head, const char *str);
void print_list(const list_t *head);
void free_list(list_t *head);

#endif
