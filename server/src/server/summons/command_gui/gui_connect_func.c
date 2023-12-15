/*
** EPITECH PROJECT, 2023
** gui_connect_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/infos.h>
#include <zappy/server/summon/utils.h>

static void check_connected_clients(server_t *server, client_node_t *client)
{
    client_node_t *tmp = server->clients.head;
    int team_ind = 0;

    if (!tmp)
        return;
    for (u_int i = 0; i < server->clients.length; i++) {
        if (tmp->state == AI) {
            team_ind = find_team_by_uuid(tmp->uuid_team, server);
            dprintf(client->cfd, DISPATCH_PNW, tmp->cfd, tmp->stats.pos.x,
                    tmp->stats.pos.y, tmp->stats.orientation, tmp->stats.level,
                    server->teams[team_ind]->team_name);
        }
        tmp = tmp->next;
    }
}

int gui_connect_func(server_t *server, char *args[], client_node_t *client)
{
    if (!server || !args || !client)
        return FAILURE;
    msz_func(server, args, client);
    sgt_func(server, args, client);
    mct_func(server, args, client);
    tna_func(server, args, client);
    check_connected_clients(server, client);
    client->state = GUI;
    return SUCCESS;
}
