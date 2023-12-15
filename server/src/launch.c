/*
** EPITECH PROJECT, 2023
** src
** File description:
** launch
*/

#include <signal.h>
#include <stdio.h>
#include <zappy/config/config.h>
#include <zappy/server.h>
#include <zappy/server/destroy.h>

int launch(args_config_t *args)
{
    server_t server = {0};

    if (!args || create_server(&server, args) != SUCCESS)
        return FAILURE;
    set_server(&server);
    printf("Port: %d\n", args->port);
    signal(SIGINT, &handle_sigint);
    destroy_arguments(args);
    return server_loop(&server);
}
