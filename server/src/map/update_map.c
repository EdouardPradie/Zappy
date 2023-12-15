/*
** EPITECH PROJECT, 2023
** map
** File description:
** update_map
*/

#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/map_utils.h>
#include <zappy/server/summon/utils.h>

static int find_stocks(map_t map, u_int ind)
{
    int stock = 0;

    for (u_int y = 0; y < map.size.y; y++)
        for (u_int x = 0; x < map.size.x; x++)
            stock += map.tiles[y][x].slots[ind].units;
    return stock;
}

static void send_infos(server_t *server)
{
    client_node_t *node = server->clients.head;

    for (u_int i = 0; i < server->clients.length; i++) {
        if (node->state == GUI)
            mct_func(server, NULL, node);
        node = node->next;
    }
}

int update_map(server_t *server)
{
    int tmp = 0;
    int stocks[INVENTORY_SLOTS] = {0};
    vector2i_t pos = {0};

    if (!server)
        return FAILURE;
    for (u_int i = 0; i < INVENTORY_SLOTS; i++)
        stocks[i] = server->map.current_stocks[i] - find_stocks(server->map, i);
    while (has_stock_left(stocks)) {
        tmp = rand() % INVENTORY_SLOTS;
        pos = (vector2i_t){rand() % server->map.size.x,
                            rand() % server->map.size.y};
        server->map.tiles[pos.y][pos.x].slots[tmp].units +=
            stock(server->map.size, DENSITY_INVENTORY[tmp], &(stocks[tmp]));
    }
    send_infos(server);
    return SUCCESS;
}
