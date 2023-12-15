/*
** EPITECH PROJECT, 2023
** client
** File description:
** add_client_to_team
*/

#include <stdio.h>
#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/map_utils.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static void update_stocks(server_t *server)
{
    for (u_int i = 0; i < INVENTORY_SLOTS; i++) {
        server->map.current_stocks[i] += server->map.init_stock[i];
    }
}

static int add_one_client_uuid(server_t *s, client_node_t *client,
                                vector2i_t pos)
{
    ssize_t size = 0;

    if ((size = array_len(s->map.tiles[pos.y][pos.x].players_uuid)) < 0)
        size = 0;
    s->map.tiles[pos.y][pos.x].players_uuid = realloc(
        s->map.tiles[pos.y][pos.x].players_uuid, sizeof(char *) * (size + 2));
    if (!s->map.tiles[pos.y][pos.x].players_uuid)
        return FAILURE;
    s->map.tiles[pos.y][pos.x].players_uuid[size + 1] = NULL;
    s->map.tiles[pos.y][pos.x].players_uuid[size] = client->uuid;
    return SUCCESS;
}

static int init_client(server_t *server, client_node_t *client, team_t *team,
                        int team_ind)
{
    char output[BUFFER_SIZE] = {0};

    client->stats.pos.x = rand() % server->map.size.x;
    client->stats.pos.y = rand() % server->map.size.y;
    server->teams[team_ind]->init_clients--;
    add_one_client_uuid(server, client, client->stats.pos);
    dprintf(client->cfd, "%zu\n%zu %zu\n",
            team->spots_free + team->init_clients, server->map.size.x,
            server->map.size.y);
    sprintf(output, DISPATCH_PNW, client->cfd, client->stats.pos.x,
            client->stats.pos.y, client->stats.orientation, client->stats.level,
            team->team_name);
    send_toall_guicli(server, output);
    update_stocks(server);
    return SUCCESS;
}

static int add_client_from_egg(client_node_t *client, server_t *server,
                                team_t **team)
{
    char output[BUFFER_SIZE] = {0};

    (*team)->spots_free--;
    if (array_len((*team)->eggs) < (*team)->spots_free)
        return set_error(client->cfd, INVALID_ACTION, false);
    sprintf(output, DISPATCH_EBO, (*team)->eggs[(*team)->spots_free]->nb);
    from_egg_to_player_tile(server, client, (*team)->eggs[(*team)->spots_free]);
    client->stats.pos = (*team)->eggs[(*team)->spots_free]->pos;
    free((*team)->eggs[(*team)->spots_free]);
    (*team)->eggs[(*team)->spots_free] = NULL;
    dprintf(client->cfd, "%zu\n%zu %zu\n",
            (*team)->spots_free + (*team)->init_clients, server->map.size.x,
            server->map.size.y);
    send_toall_guicli(server, output);
    sprintf(output, DISPATCH_PNW, client->cfd, client->stats.pos.x,
            client->stats.pos.y, client->stats.orientation, client->stats.level,
            (*team)->team_name);
    send_toall_guicli(server, output);
    return SUCCESS;
}

int add_client_to_team(client_node_t *client, server_t *server,
                        const char *team_name)
{
    int team_ind = -1;

    if (!client || !server || !team_name)
        return FAILURE;
    if ((team_ind = find_team_by_name(team_name, server)) < 0)
        return set_error(client->cfd, UNKNOWN_COMMAND, false);
    if (server->teams[team_ind]->spots_free <= 0 &&
        server->teams[team_ind]->init_clients <= 0)
        return set_error(client->cfd, INVALID_ACTION, false);
    client->state = AI;
    client->uuid_team = server->teams[team_ind]->uuid;
    server->teams[team_ind]->uuid_clients[server->teams[team_ind]->nb_clients -
        (server->teams[team_ind]->init_clients +
            server->teams[team_ind]->spots_free)] = client->uuid;
    if (server->teams[team_ind]->init_clients == 0)
        return add_client_from_egg(client, server, &server->teams[team_ind]);
    return init_client(server, client, server->teams[team_ind], team_ind);
}
