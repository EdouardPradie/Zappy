/*
** EPITECH PROJECT, 2023
** options
** File description:
** y_handler
*/

#include <stdlib.h>
#include <unistd.h>
#include <zappy/config/arguments.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

int y_handler(args_config_t *args, char __attribute__((unused)) *const argv[],
            int __attribute__((unused)) argc)
{
    if (!strisnum(optarg))
        return set_error(STDERR_FILENO, ERROR_HEIGHT, false);
    if ((args->world.y = atoi(optarg)) <= 0)
        return set_error(STDERR_FILENO, ERROR_HEIGHT, false);
    return SUCCESS;
}
