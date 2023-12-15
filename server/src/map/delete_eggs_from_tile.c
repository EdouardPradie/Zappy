/*
** EPITECH PROJECT, 2023
** map
** File description:
** delete_eggs_from_tile
*/

#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/map_utils.h>

bool delete_eggs_from_tile(server_t *server, vector2i_t pos)
{
    if (!server)
        return false;
    if (!server->map.tiles[pos.y][pos.x].eggs)
        return false;
    for (u_int i = 0; server->map.tiles[pos.y][pos.x].eggs[i] > -1; i++) {
        delete_egg_from_team(server, server->map.tiles[pos.y][pos.x].eggs[i]);
    }
    free(server->map.tiles[pos.y][pos.x].eggs);
    server->map.tiles[pos.y][pos.x].eggs = NULL;
    return true;
}
