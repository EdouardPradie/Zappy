/*
** EPITECH PROJECT, 2023
** connect_nbr_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/infos.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

int connect_nbr_func(server_t *server, char *args[], client_node_t *client)
{
    int team_ind = -1;

    if (!server || !client)
        return FAILURE;
    if (!args || array_len(args) != 1)
        return set_error(client->cfd, INVALID_ACTION, false);
    if ((team_ind = find_team_by_uuid(client->uuid_team, server)) < 0)
        return set_error(client->cfd, INVALID_ACTION, false);
    dprintf(client->cfd, "%zu\n",
            server->teams[team_ind]->spots_free +
                server->teams[team_ind]->init_clients);
    return SUCCESS;
}
