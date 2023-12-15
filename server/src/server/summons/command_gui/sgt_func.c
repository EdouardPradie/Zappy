/*
** EPITECH PROJECT, 2023
** sgt_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>

int sgt_func(server_t *server, char __attribute__((unused)) * args[],
            client_node_t *client)
{
    if (!client || !server)
        return FAILURE;
    dprintf(client->cfd, DISPATCH_SGT, server->clock.freq);
    return SUCCESS;
}
