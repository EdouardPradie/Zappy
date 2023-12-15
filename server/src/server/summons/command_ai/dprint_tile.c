/*
** EPITECH PROJECT, 2023
** dprint_tile
** File description:
** zappy
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <zappy/server/utils.h>

static size_t check_cord(size_t csize, ssize_t cord)
{
    size_t result = cord;

    if (cord < 0)
        result = csize + cord;
    if ((size_t)result >= csize)
        result %= csize;
    return result;
}

void dprint_tile(map_t map, ssize_t cord_x, ssize_t cord_y,
                    client_node_t *client)
{
    size_t x = check_cord(map.size.x, cord_x);
    size_t y = check_cord(map.size.y, cord_y);

    if (!client)
        return;
    for (ssize_t user = array_len(map.tiles[y][x].players_uuid); user > 0;
            user -= 1)
        dprintf(client->cfd, " player");
    for (int i = 0; i < INVENTORY_SLOTS; i += 1) {
        for (ssize_t obj = map.tiles[y][x].slots[i].units; obj > 0; obj -= 1)
            dprintf(client->cfd, " %s", RESOURCES_INVENTORY[i]);
    }
}
