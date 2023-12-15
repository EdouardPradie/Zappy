/*
** EPITECH PROJECT, 2023
** destroy
** File description:
** destroy_arguments
*/

#include <stdlib.h>
#include <zappy/config/arguments.h>
#include <zappy/server.h>

int destroy_arguments(args_config_t *args)
{
    if (!args)
        return FAILURE;
    free(args->team_names);
    return SUCCESS;
}
