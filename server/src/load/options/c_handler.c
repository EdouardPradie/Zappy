/*
** EPITECH PROJECT, 2023
** options
** File description:
** c_handler
*/

#include <stdlib.h>
#include <unistd.h>
#include <zappy/config/arguments.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

int c_handler(args_config_t *args, char __attribute__((unused)) *const argv[],
            int __attribute__((unused)) argc)
{
    if (!strisnum(optarg))
        return set_error(STDERR_FILENO, ERROR_CLIENTS, false);
    if ((args->nb_clients_og = atoi(optarg)) <= 0)
        return set_error(STDERR_FILENO, ERROR_CLIENTS, false);
    return SUCCESS;
}
