/*
** EPITECH PROJECT, 2023
** take_func
** File description:
** zappy
*/

#include <stdio.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static void send_new_inventory_to_gui(server_t *server, client_node_t *client)
{
    char output[BUFFER_SIZE] = {0};

    sprintf(output, DISPATCH_PIN, client->cfd, client->stats.pos.x,
            client->stats.pos.y, client->stats.inventory[FOOD].units,
            client->stats.inventory[LINEMATE].units,
            client->stats.inventory[DERAUMERE].units,
            client->stats.inventory[SIBUR].units,
            client->stats.inventory[MENDIANE].units,
            client->stats.inventory[PHIRAS].units,
            client->stats.inventory[THYSTAME].units);
    send_toall_guicli(server, output);
}

static void send_infos(server_t *server, client_node_t *client, int ind)
{
    char output[BUFFER_SIZE] = {0};
    vector2i_t pos = client->stats.pos;

    sprintf(output, DISPATCH_PGT, client->cfd,
            client->stats.inventory[ind].resource);
    send_toall_guicli(server, output);
    sprintf(output, DISPATCH_BCT, pos.x, pos.y,
            server->map.tiles[pos.y][pos.x].slots[FOOD].units,
            server->map.tiles[pos.y][pos.x].slots[LINEMATE].units,
            server->map.tiles[pos.y][pos.x].slots[DERAUMERE].units,
            server->map.tiles[pos.y][pos.x].slots[SIBUR].units,
            server->map.tiles[pos.y][pos.x].slots[MENDIANE].units,
            server->map.tiles[pos.y][pos.x].slots[PHIRAS].units,
            server->map.tiles[pos.y][pos.x].slots[THYSTAME].units);
    send_toall_guicli(server, output);
    send_new_inventory_to_gui(server, client);
    dprintf(client->cfd, BASIC_VALID);
}

int take_func(server_t *server, char *args[], client_node_t *client)
{
    if (!server || !client)
        return FAILURE;
    if (!args || array_len(args) != 2)
        return set_error(client->cfd, INVALID_ACTION, false);
    for (int i = 0; i < INVENTORY_SLOTS; i += 1) {
        if (server->map.tiles[client->stats.pos.y][client->stats.pos.x]
                    .slots[i]
                    .units > 0 &&
            strcmp(RESOURCES_INVENTORY[i], args[1]) == 0) {
            client->stats.inventory[i].units += 1;
            server->map.tiles[client->stats.pos.y][client->stats.pos.x]
                .slots[i]
                .units -= 1;
            send_infos(server, client, i);
            add_ticks_occupied(client, RESTRAINT_TAKE, server);
            return SUCCESS;
        }
    }
    return set_error(client->cfd, INVALID_ACTION, false);
}
