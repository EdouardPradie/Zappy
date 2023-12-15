/*
** EPITECH PROJECT, 2023
** look_func
** File description:
** zappy
*/

#include <stddef.h>
#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static int look_west(server_t *server, client_node_t *client)
{
    dprint_tile(server->map, client->stats.pos.x, client->stats.pos.y, client);
    for (ssize_t i = 1; i <= (ssize_t)client->stats.level; i += 1) {
        for (ssize_t j = -i; j < (i + 1); j += 1) {
            dprintf(client->cfd, ",");
            dprint_tile(server->map, client->stats.pos.x - i,
                        client->stats.pos.y - j, client);
        }
    }
    return SUCCESS;
}

static int look_east(server_t *server, client_node_t *client)
{
    dprint_tile(server->map, client->stats.pos.x, client->stats.pos.y, client);
    for (ssize_t i = 1; i <= (ssize_t)client->stats.level; i += 1) {
        for (ssize_t j = -i; j < (i + 1); j += 1) {
            dprintf(client->cfd, ",");
            dprint_tile(server->map, client->stats.pos.x + i,
                        client->stats.pos.y + j, client);
        }
    }
    return SUCCESS;
}

static int look_south(server_t *server, client_node_t *client)
{
    dprint_tile(server->map, client->stats.pos.x, client->stats.pos.y, client);
    for (ssize_t i = 1; i <= (ssize_t)client->stats.level; i += 1) {
        for (ssize_t j = -i; j < (i + 1); j += 1) {
            dprintf(client->cfd, ",");
            dprint_tile(server->map, client->stats.pos.x + j,
                        client->stats.pos.y + i, client);
        }
    }
    return SUCCESS;
}

static int look_north(server_t *server, client_node_t *client)
{
    dprint_tile(server->map, client->stats.pos.x, client->stats.pos.y, client);
    for (ssize_t i = 1; i <= (ssize_t)client->stats.level; i += 1) {
        for (ssize_t j = -i; j < (i + 1); j += 1) {
            dprintf(client->cfd, ",");
            dprint_tile(server->map, client->stats.pos.x + j,
                        client->stats.pos.y - i, client);
        }
    }
    return SUCCESS;
}

int look_func(server_t *server, char *args[], client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    if (!args || array_len(args) != 1)
        return set_error(client->cfd, INVALID_ACTION, false);
    dprintf(client->cfd, "[ ");
    switch (client->stats.orientation) {
        case NORTH: look_north(server, client); break;
        case SOUTH: look_south(server, client); break;
        case EAST: look_east(server, client); break;
        case WEST: look_west(server, client); break;
    }
    dprintf(client->cfd, " ]\n");
    add_ticks_occupied(client, RESTRAINT_LOOK, server);
    return SUCCESS;
}
