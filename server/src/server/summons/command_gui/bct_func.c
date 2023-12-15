/*
** EPITECH PROJECT, 2023
** bct_func
** File description:
** zappy
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>
#include <zappy/server/utils.h>

int bct_func(server_t *server, char *args[], client_node_t *client)
{
    ssize_t x = 0;
    ssize_t y = 0;

    if (!args || array_len(args) != 3 || !server || !client)
        return FAILURE;
    x = atoi(args[1]);
    y = atoi(args[2]);
    if (x < 0 || !strisnum(args[1]) || y < 0 || !strisnum(args[2]))
        return FAILURE;
    if ((size_t)x >= server->map.size.x || (size_t)y >= server->map.size.y)
        return FAILURE;
    dprintf(client->cfd, DISPATCH_BCT, x, y,
            server->map.tiles[y][x].slots[FOOD].units,
            server->map.tiles[y][x].slots[LINEMATE].units,
            server->map.tiles[y][x].slots[DERAUMERE].units,
            server->map.tiles[y][x].slots[SIBUR].units,
            server->map.tiles[y][x].slots[MENDIANE].units,
            server->map.tiles[y][x].slots[PHIRAS].units,
            server->map.tiles[y][x].slots[THYSTAME].units);
    return SUCCESS;
}
