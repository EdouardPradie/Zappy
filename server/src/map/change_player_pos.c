/*
** EPITECH PROJECT, 2023
** map
** File description:
** change_player_pos
*/

#include <stdlib.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

static bool is_tile(map_t *map, vector2i_t pos)
{
    if (map->size.x < pos.x || map->size.y < pos.y)
        return false;
    return true;
}

static int swap_tiles(server_t *srv, u_int ind, vector2i_t old, vector2i_t pos)
{
    int len = array_len(srv->map.tiles[pos.y][pos.x].players_uuid);

    if (len <= 0)
        len = 1;
    srv->map.tiles[pos.y][pos.x].players_uuid =
        realloc_array(srv->map.tiles[pos.y][pos.x].players_uuid, len,
                    strlen(srv->map.tiles[old.y][old.x].players_uuid[ind]));
    if (!srv->map.tiles[pos.y][pos.x].players_uuid)
        return FAILURE;
    srv->map.tiles[pos.y][pos.x].players_uuid[len - 1] =
        srv->map.tiles[old.y][old.x].players_uuid[ind];
    if (ind == 0) {
        free(srv->map.tiles[old.y][old.x].players_uuid);
        srv->map.tiles[old.y][old.x].players_uuid = NULL;
    } else
        srv->map.tiles[old.y][old.x].players_uuid =
            delete_from_array(srv->map.tiles[old.y][old.x].players_uuid, ind);
    return SUCCESS;
}

int change_player_pos(server_t *server, const char *client, vector2i_t old_pos,
                    vector2i_t new_pos)
{
    u_int ind = 0;

    if (!server || !client)
        return FAILURE;
    if (!is_tile(&server->map, old_pos) || !is_tile(&server->map, new_pos))
        return FAILURE;
    if (!server->map.tiles[old_pos.y][old_pos.x].players_uuid)
        return FAILURE;
    for (; server->map.tiles[old_pos.y][old_pos.x].players_uuid[ind]; ind++)
        if (strcmp(server->map.tiles[old_pos.y][old_pos.x].players_uuid[ind],
                    client) == SUCCESS)
            return swap_tiles(server, ind, old_pos, new_pos);
    return FAILURE;
}
