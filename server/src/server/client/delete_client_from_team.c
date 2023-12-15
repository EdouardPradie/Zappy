/*
** EPITECH PROJECT, 2023
** client
** File description:
** delete_client_from_team
*/

#include <string.h>
#include <zappy/server.h>
#include <zappy/server/client.h>

void delete_client_from_team(client_node_t *client, server_t *server)
{
    int team_ind = -1;

    if (!client || !server ||
        (team_ind = find_team_by_uuid(client->uuid_team, server)) < 0)
        return;
    for (unsigned int i = 0; i < server->teams[team_ind]->nb_clients &&
            server->teams[team_ind]->uuid_clients[i]; i++) {
        if (!strcmp(client->uuid, server->teams[team_ind]->uuid_clients[i])) {
            server->teams[team_ind]->uuid_clients[i] = NULL;
            break;
        }
    }
    server->teams[team_ind]->nb_clients--;
}
