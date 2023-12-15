/*
** EPITECH PROJECT, 2023
** forward_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/map_utils.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

int forward_north(server_t *server, client_node_t *client)
{
    vector2i_t new_pos = client->stats.pos;

    if (client->stats.pos.y == 0)
        new_pos.y = server->map.size.y - 1;
    else
        new_pos.y -= 1;
    change_player_pos(server, client->uuid, client->stats.pos, new_pos);
    client->stats.pos = new_pos;
    return SUCCESS;
}

int forward_south(server_t *server, client_node_t *client)
{
    vector2i_t new_pos = client->stats.pos;

    if (client->stats.pos.y < (server->map.size.y - 1))
        new_pos.y += 1;
    else
        new_pos.y = 0;
    change_player_pos(server, client->uuid, client->stats.pos, new_pos);
    client->stats.pos = new_pos;
    return SUCCESS;
}

int forward_east(server_t *server, client_node_t *client)
{
    vector2i_t new_pos = client->stats.pos;

    if (client->stats.pos.x < (server->map.size.x - 1))
        new_pos.x += 1;
    else
        new_pos.x = 0;
    change_player_pos(server, client->uuid, client->stats.pos, new_pos);
    client->stats.pos = new_pos;
    return SUCCESS;
}

int forward_west(server_t *server, client_node_t *client)
{
    vector2i_t new_pos = client->stats.pos;

    if (client->stats.pos.x == 0)
        new_pos.x = server->map.size.x - 1;
    else
        new_pos.x -= 1;
    change_player_pos(server, client->uuid, client->stats.pos, new_pos);
    client->stats.pos = new_pos;
    return SUCCESS;
}

int forward_func(server_t *server, char *args[], client_node_t *client)
{
    char output[BUFFER_SIZE] = {0};

    if (!server || !client)
        return FAILURE;
    if (!args || array_len(args) != 1 || client->stats.action.type != NOTHING)
        return set_error(client->cfd, INVALID_ACTION, false);
    switch (client->stats.orientation) {
        case NORTH: forward_north(server, client); break;
        case SOUTH: forward_south(server, client); break;
        case EAST: forward_east(server, client); break;
        case WEST: forward_west(server, client); break;
    }
    add_ticks_occupied(client, RESTRAINT_FORWARD, server);
    sprintf(output, DISPATCH_PPO, client->cfd, client->stats.pos.x,
            client->stats.pos.y, client->stats.orientation);
    send_toall_guicli(server, output);
    dprintf(client->cfd, BASIC_VALID);
    return SUCCESS;
}
