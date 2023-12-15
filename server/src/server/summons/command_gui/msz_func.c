/*
** EPITECH PROJECT, 2023
** msz_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>

int msz_func(server_t *server, char __attribute__((unused)) * args[],
            client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    dprintf(client->cfd, DISPATCH_MSZ, server->map.size.x, server->map.size.y);
    return SUCCESS;
}
