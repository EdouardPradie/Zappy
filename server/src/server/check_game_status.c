/*
** EPITECH PROJECT, 2023
** server
** File description:
** check_game_status
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/summon/utils.h>

static int check_team_win(server_t *server, team_t *team)
{
    client_node_t *client = NULL;
    int lvl_enough = 0;

    if (!team->uuid_clients)
        return FAILURE;
    for (u_int i = 0; team->uuid_clients[i]; i++) {
        if (!(client = find_client_by_uuid(team->uuid_clients[i], server)))
            continue;
        if (client->stats.level >= LVL_REQUIRED)
            lvl_enough++;
    }
    return lvl_enough >= CLIENTS_REQUIRED ? SUCCESS : FAILURE;
}

static int finish_game(server_t *server, team_t *team)
{
    char output[BUFFER_SIZE] = {0};

    sprintf(output, DISPATCH_SEG, team->team_name);
    send_toall_guicli(server, output);
    server->running = false;
    return SUCCESS;
}

int check_game_status(server_t *server)
{
    if (!server || !server->teams)
        return FAILURE;
    for (u_int i = 0; server->teams[i]; i++) {
        if (server->teams[i]->nb_clients < CLIENTS_REQUIRED)
            continue;
        if (check_team_win(server, server->teams[i]) == SUCCESS)
            return finish_game(server, server->teams[i]);
    }
    return FAILURE;
}
