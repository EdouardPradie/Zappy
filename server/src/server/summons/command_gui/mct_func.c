/*
** EPITECH PROJECT, 2023
** mct_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>

int mct_func(server_t *server, char __attribute__((unused)) * args[],
                client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    for (ssize_t pos_y = 0; server->map.tiles[pos_y] != NULL; pos_y++) {
        for (ssize_t pos_x = 0; !server->map.tiles[pos_y][pos_x].end; pos_x++) {
            dprintf(client->cfd, DISPATCH_BCT, pos_x, pos_y,
                    server->map.tiles[pos_y][pos_x].slots[FOOD].units,
                    server->map.tiles[pos_y][pos_x].slots[LINEMATE].units,
                    server->map.tiles[pos_y][pos_x].slots[DERAUMERE].units,
                    server->map.tiles[pos_y][pos_x].slots[SIBUR].units,
                    server->map.tiles[pos_y][pos_x].slots[MENDIANE].units,
                    server->map.tiles[pos_y][pos_x].slots[PHIRAS].units,
                    server->map.tiles[pos_y][pos_x].slots[THYSTAME].units);
        }
    }
    return SUCCESS;
}
