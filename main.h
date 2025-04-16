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

char *get_command(char *name, list_t **paths);

char *_getenv(const char *name);
list_t *create_path_list(char *value);

list_t *add_node_end(list_t **head, const char *str);
void print_list(const list_t *head);
void free_list(list_t *head);

#endif
