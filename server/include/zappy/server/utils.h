/*
** EPITECH PROJECT, 2023
** server
** File description:
** utils
*/

#pragma once

#include <stdbool.h>
#include <zappy/server/infos.h>

#define QUOTATION "\""

ssize_t array_len(void *);
int char_in_str(const char *, char);
void free_array(void *);
char *generate_uuid(void);
int print_help(int);
int set_error(int, char *, bool);
bool strisnum(const char *);
char *strndup_quotes(const char *, size_t);
char **str_to_array(const char *, char *);
char **realloc_array(char **, u_int, u_int);
char **delete_from_array(char **, u_int);
