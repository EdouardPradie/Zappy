/*
** EPITECH PROJECT, 2023
** command_ai
** File description:
** utils_incantation
*/

#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/utils.h>

bool mandatory_resources(server_t *server, vector2i_t pos, int lvl)
{
    tile_t tile = {0};

    if (!server || pos.y >= server->map.size.y || pos.x >= server->map.size.y)
        return false;
    tile = server->map.tiles[pos.y][pos.x];
    return (
        (INCANTATION_MANDATORY[lvl - 1][1] - CHAR_INT) <= tile.slots[1].units &&
        (INCANTATION_MANDATORY[lvl - 1][2] - CHAR_INT) <= tile.slots[2].units &&
        (INCANTATION_MANDATORY[lvl - 1][3] - CHAR_INT) <= tile.slots[3].units &&
        (INCANTATION_MANDATORY[lvl - 1][4] - CHAR_INT) <= tile.slots[4].units &&
        (INCANTATION_MANDATORY[lvl - 1][5] - CHAR_INT) <= tile.slots[5].units &&
        (INCANTATION_MANDATORY[lvl - 1][6] - CHAR_INT) <= tile.slots[6].units);
}

bool loop_clients_level_up(server_t *server, client_node_t *client)
{
    int players_able = 0;
    client_node_t *tmp = NULL;
    char **cli_tile = NULL;

    if (!server || !client ||
        !(cli_tile = server->map.tiles[client->stats.pos.y][client->stats.pos.x]
                        .players_uuid))
        return false;
    for (int i = 0; cli_tile[i] != NULL; i += 1) {
        tmp = find_client_by_uuid(cli_tile[i], server);
        if (!tmp)
            continue;
        if (tmp->stats.level == client->stats.level)
            players_able += 1;
    }
    return players_able >=
        (INCANTATION_MANDATORY[client->stats.level - 1][0] - CHAR_INT);
}

char *fill_broadcast_summon(char *args[], char *message)
{
    int idx = 0;

    for (int i = 1; args[i] != NULL; i += 1) {
        for (int j = 0; args[i][j] != '\0'; j += 1) {
            message[idx] = args[i][j];
            idx += 1;
        }
        message[idx] = ' ';
        idx += 1;
    }
    return message;
}
