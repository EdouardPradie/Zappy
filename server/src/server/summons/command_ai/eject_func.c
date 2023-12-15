/*
** EPITECH PROJECT, 2023
** eject_func
** File description:
** zappy
*/

#include <stdio.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/map_utils.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

bool same_tile(vector2i_t a, vector2i_t b)
{
    return (a.x == b.x && a.y == b.y);
}

static void check_orientation(server_t *server, client_node_t *tmp,
                                client_node_t *client)
{
    switch (client->stats.orientation) {
        case NORTH: forward_north(server, tmp); break;
        case SOUTH: forward_south(server, tmp); break;
        case EAST: forward_east(server, tmp); break;
        case WEST: forward_west(server, tmp); break;
    }
}

static void send_ejected_infos(client_node_t *cli, server_t *server,
                                orientation_t orientation)
{
    char output[BUFFER_SIZE] = {0};

    dprintf(cli->cfd, AI_EJECT, orientation);
    sprintf(output, DISPATCH_PPO, cli->cfd, cli->stats.pos.x, cli->stats.pos.y,
            cli->stats.orientation);
    send_toall_guicli(server, output);
}

static int send_ejecter_infos(client_node_t *client, server_t *server, int ind)
{
    char output[BUFFER_SIZE] = {0};

    sprintf(output, DISPATCH_PEX, client->cfd);
    send_toall_guicli(server, output);
    dprintf(client->cfd, ind > 0 ? BASIC_VALID : INVALID_ACTION);
    return SUCCESS;
}

int eject_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = NULL;
    int eject = 0;

    if (!server || !client)
        return FAILURE;
    if (!args || array_len(args) != 1 || !(tmp = server->clients.head))
        return set_error(client->cfd, INVALID_ACTION, false);
    for (unsigned int ind = 0; ind < server->clients.length; ind++) {
        if (same_tile(tmp->stats.pos, client->stats.pos) &&
            strcmp(tmp->uuid, client->uuid) != SUCCESS) {
            check_orientation(server, tmp, client);
            send_ejected_infos(tmp, server, client->stats.orientation);
            eject++;
        }
        tmp = tmp->next;
    }
    eject += delete_eggs_from_tile(server, client->stats.pos);
    add_ticks_occupied(client, RESTRAINT_EJECT, server);
    return send_ejecter_infos(client, server, eject);
}
