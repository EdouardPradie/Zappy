/*
** EPITECH PROJECT, 2023
** command_ai
** File description:
** check_incantation_end
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/summon/utils.h>

static void stop_incantation_client(client_node_t *node)
{
    node->stats.action.type = NOTHING;
    node->stats.action.ticks = -1;
    dprintf(node->cfd, INVALID_ACTION);
}

static void stop_incantation(server_t *server, client_node_t *client)
{
    client_node_t *node = NULL;
    int idx = (INCANTATION_MANDATORY[client->stats.level - 1][0] - CHAR_INT);
    char **clients = server->map.tiles[client->stats.pos.y][client->stats.pos.x]
                        .players_uuid;
    char output[BUFFER_SIZE] = {0};

    if (!clients)
        return;
    for (int i = 0; clients[i] != NULL && idx > 0; i += 1) {
        node = find_client_by_uuid(clients[i], server);
        if (!node)
            continue;
        if (node->stats.level == client->stats.level &&
            node->stats.action.type == INCANTATION) {
            stop_incantation_client(node);
            idx -= 1;
        }
    }
    sprintf(output, DISPATCH_PIE, client->stats.pos.x, client->stats.pos.y, 0);
    send_toall_guicli(server, output);
}

static void finish_incantation_client(server_t *server, client_node_t *node)
{
    char output[BUFFER_SIZE] = {0};

    node->stats.level += 1;
    node->stats.action.type = NOTHING;
    node->stats.action.ticks = -1;
    dprintf(node->cfd, VALID_INCANT, node->stats.level);
    sprintf(output, DISPATCH_PLV, node->cfd, node->stats.level);
    send_toall_guicli(server, output);
}

static void finish_incantation(server_t *s, client_node_t *c)
{
    client_node_t *node = NULL;
    int idx = (INCANTATION_MANDATORY[c->stats.level - 1][0] - CHAR_INT);
    char **clients = s->map.tiles[c->stats.pos.y][c->stats.pos.x].players_uuid;
    char output[BUFFER_SIZE] = {0};

    sprintf(output, DISPATCH_PIE, c->stats.pos.x, c->stats.pos.y, 1);
    send_toall_guicli(s, output);
    for (int i = 0; clients[i] != NULL && idx > 0; i += 1) {
        node = find_client_by_uuid(clients[i], s);
        if (!node)
            continue;
        if (node->stats.level == c->stats.level &&
            node->stats.action.type == INCANTATION) {
            finish_incantation_client(s, node);
            idx -= 1;
        }
    }
}

int check_incantation_end(server_t *server, client_node_t *client, int ticks)
{
    if (!server || !client)
        return FAILURE;
    if (ticks < client->stats.action.ticks)
        return FAILURE;
    if (!mandatory_resources(server, client->stats.pos, client->stats.level) ||
        !loop_clients_level_up(server, client)) {
        stop_incantation(server, client);
        return FAILURE;
    }
    finish_incantation(server, client);
    return SUCCESS;
}
