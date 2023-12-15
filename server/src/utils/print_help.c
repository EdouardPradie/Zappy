/*
** EPITECH PROJECT, 2023
** utils
** File description:
** print_help
*/

#include <string.h>
#include <unistd.h>
#include <zappy/server.h>

int print_help(int ret_value)
{
    write(STDOUT_FILENO, HELP, strlen(HELP));
    return ret_value;
}
