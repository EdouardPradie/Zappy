/*
** EPITECH PROJECT, 2023
** incantation_func
** File description:
** zappy
*/

#include <stdio.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static void finish_start_incant(server_t *s, client_node_t *c, char *output,
                                int offset)
{
    offset += sprintf(output + offset, "\n");
    add_ticks_occupied(c, RESTRAINT_INCANTATION, s);
    c->stats.action.type = INCANTATION;
    dprintf(c->cfd, IN_INCANT);
    send_toall_guicli(s, output);
}

static void in_incantation(server_t *s, client_node_t *c)
{
    client_node_t *tmp = NULL;
    int idx = (INCANTATION_MANDATORY[c->stats.level - 1][0] - CHAR_INT);
    char **cli_in_tile =
        s->map.tiles[c->stats.pos.y][c->stats.pos.x].players_uuid;
    char output[BUFFER_SIZE] = {0};
    int offset = 0;

    offset += sprintf(output, DISPATCH_PIC, c->stats.pos.x, c->stats.pos.y,
                        c->stats.level, c->cfd);
    for (int i = 0; cli_in_tile[i] != NULL && idx > 1; i += 1) {
        tmp = find_client_by_uuid(cli_in_tile[i], s);
        if (tmp->stats.level == c->stats.level) {
            offset += sprintf(output + offset, " %d", tmp->cfd);
            add_ticks_occupied(tmp, RESTRAINT_INCANTATION, s);
            tmp->stats.action.type = INCANTATION;
            dprintf(tmp->cfd, IN_INCANT);
            idx -= 1;
        }
    }
    finish_start_incant(s, c, output, offset);
}

static int failed_incantation(server_t *server, client_node_t *client)
{
    char output[BUFFER_SIZE] = {0};

    add_ticks_occupied(client, RESTRAINT_INCANTATION, server);
    dprintf(client->cfd, INVALID_ACTION);
    client->stats.action.type = INCANTATION;
    sprintf(output, "pic %zu %zu %zu %d\n", client->stats.pos.x,
            client->stats.pos.y, client->stats.level, client->cfd);
    send_toall_guicli(server, output);
    return FAILURE;
}

int incantation_func(server_t *server, char *args[], client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    if (!args || array_len(args) != 1)
        return set_error(client->cfd, INVALID_ACTION, false);
    if (mandatory_resources(server, client->stats.pos, client->stats.level) &&
        loop_clients_level_up(server, client)) {
        in_incantation(server, client);
        return SUCCESS;
    }
    return failed_incantation(server, client);
}
