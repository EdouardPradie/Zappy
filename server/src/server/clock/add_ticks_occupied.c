/*
** EPITECH PROJECT, 2023
** clock
** File description:
** add_ticks_occupied
*/

#include <zappy/server.h>
#include <zappy/server/clock/utils.h>

int add_ticks_occupied(client_node_t *client, int restraint, server_t *server)
{
    if (!client || !server)
        return FAILURE;
    client->stats.action.type = ACTION;
    client->stats.action.ticks = gettickselapsed(&server->clock) + restraint;
    return SUCCESS;
}
