/*
** EPITECH PROJECT, 2023
** left_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static void send_infos(server_t *server, client_node_t *client)
{
    char output[BUFFER_SIZE] = {0};

    sprintf(output, DISPATCH_PPO, client->cfd, client->stats.pos.x,
            client->stats.pos.y, client->stats.orientation);
    send_toall_guicli(server, output);
    dprintf(client->cfd, BASIC_VALID);
}

static int set_client_orientation(server_t *server, client_node_t *client,
                                orientation_t orientation)
{
    client->stats.orientation = orientation;
    add_ticks_occupied(client, RESTRAINT_LEFT, server);
    send_infos(server, client);
    return SUCCESS;
}

int left_func(server_t *server, char __attribute__((unused)) * args[],
                client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    switch (client->stats.orientation) {
        case NORTH: return set_client_orientation(server, client, WEST);
        case SOUTH: return set_client_orientation(server, client, EAST);
        case EAST: return set_client_orientation(server, client, NORTH);
        case WEST: return set_client_orientation(server, client, SOUTH); break;
    }
    return set_error(client->cfd, INVALID_ACTION, false);
}
