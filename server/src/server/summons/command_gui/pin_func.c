/*
** EPITECH PROJECT, 2023
** pin_func
** File description:
** zappy
*/

#include <stdio.h>
#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

static void dispatch_infos(int fd, client_node_t *client)
{
    dprintf(fd, DISPATCH_PIN, client->cfd, client->stats.pos.x,
            client->stats.pos.y, client->stats.inventory[FOOD].units,
            client->stats.inventory[LINEMATE].units,
            client->stats.inventory[DERAUMERE].units,
            client->stats.inventory[SIBUR].units,
            client->stats.inventory[MENDIANE].units,
            client->stats.inventory[PHIRAS].units,
            client->stats.inventory[THYSTAME].units);
}

int pin_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = NULL;
    int fd = 0;

    if (!args || array_len(args) != 2 || !strisnum(args[1]) || !server ||
        !client)
        return FAILURE;
    if (!(tmp = server->clients.head) || (fd = atoi(args[1])) <= 0)
        return FAILURE;
    for (u_int ind = 0; ind < server->clients.length; ind++) {
        if (fd == tmp->cfd) {
            dispatch_infos(client->cfd, tmp);
            return SUCCESS;
        }
        tmp = tmp->next;
    }
    return FAILURE;
}
