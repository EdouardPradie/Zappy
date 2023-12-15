/*
** EPITECH PROJECT, 2023
** map
** File description:
** add_egg_to_tile
*/

#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/map_utils.h>

int add_egg_to_tile(server_t *server, vector2i_t pos, int egg)
{
    int size = 0;

    if (!server || pos.y >= server->map.size.y || pos.x >= server->map.size.x)
        return FAILURE;
    if ((size = len_eggs(server->map.tiles[pos.y][pos.x].eggs)) < 0)
        size = 0;
    server->map.tiles[pos.y][pos.x].eggs =
        realloc(server->map.tiles[pos.y][pos.x].eggs, sizeof(int) * (size + 2));
    if (!server->map.tiles[pos.y][pos.x].eggs)
        return FAILURE;
    server->map.tiles[pos.y][pos.x].eggs[size] = egg;
    server->map.tiles[pos.y][pos.x].eggs[size + 1] = -1;
    return SUCCESS;
}
