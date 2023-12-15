/*
** EPITECH PROJECT, 2023
** eggs
** File description:
** from_egg_to_player
*/

#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/map_utils.h>
#include <zappy/server/utils.h>

int from_egg_to_player(client_node_t *client, team_t **team, server_t *server)
{
    if (!client || !team || !(*team) || !server)
        return FAILURE;
    if (array_len((*team)->eggs) < (*team)->spots_free)
        return FAILURE;
    from_egg_to_player_tile(server, client, (*team)->eggs[(*team)->spots_free]);
    client->stats.pos = (*team)->eggs[(*team)->spots_free]->pos;
    free((*team)->eggs[(*team)->spots_free]);
    (*team)->eggs[(*team)->spots_free] = NULL;
    return SUCCESS;
}
