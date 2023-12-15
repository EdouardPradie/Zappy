/*
** EPITECH PROJECT, 2023
** utils
** File description:
** set_error
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <zappy/server.h>

int set_error(int fileno, char *const str, bool perr)
{
    if (!str)
        return FAILURE;
    if (perr)
        perror(str);
    else
        write(fileno, str, strlen(str));
    return FAILURE;
}
