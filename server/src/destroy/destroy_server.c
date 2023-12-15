/*
** EPITECH PROJECT, 2023
** destroy
** File description:
** destroy_server
*/

#include <stdlib.h>
#include <unistd.h>
#include <zappy/server/destroy.h>

static void free_line(tile_t *tiles, size_t size)
{
    for (u_int i = 0; !tiles[i].end && i < size; i++) {
        if (tiles[i].eggs)
            free(tiles[i].eggs);
        if (tiles[i].players_uuid)
            free(tiles[i].players_uuid);
    }
    free(tiles);
}

void destroy_server(server_t *server)
{
    if (!server)
        return;
    destroy_clients(&server->clients, server);
    destroy_teams(server->teams);
    if (!server->map.tiles)
        return;
    for (u_int i = 0; server->map.tiles[i]; i++)
        free_line(server->map.tiles[i], server->map.size.x);
    free(server->map.tiles);
    close(server->server_fd);
}
