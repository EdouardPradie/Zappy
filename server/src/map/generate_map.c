/*
** EPITECH PROJECT, 2023
** map
** File description:
** generate_map
*/

#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/map_utils.h>

static void randomize_map(server_t *server)
{
    int tmp = 0;
    int init_stock[INVENTORY_SLOTS] = {0};

    for (u_int i = 0; i < INVENTORY_SLOTS; i++) {
        server->map.init_stock[i] =
            server->map.size.x * server->map.size.y * DENSITY_INVENTORY[i];
        server->map.current_stocks[i] = server->map.init_stock[i];
        init_stock[i] = server->map.init_stock[i];
    }
    while (has_stock_left(init_stock)) {
        tmp = rand() % INVENTORY_SLOTS;
        server->map
            .tiles[rand() % server->map.size.y][rand() % server->map.size.x]
            .slots[tmp]
            .units +=
            stock(server->map.size, DENSITY_INVENTORY[tmp], &(init_stock[tmp]));
    }
}

static tile_t *set_default_tile(tile_t *tile, u_int size)
{
    for (u_int i = 0; i <= size; i++) {
        tile[i] = (tile_t){0};
        tile[i].eggs = NULL;
        tile[i].players_uuid = NULL;
    }
    tile[size] = (tile_t){0};
    tile[size].end = true;
    return tile;
}

int generate_map(server_t *server)
{
    if (!server)
        return FAILURE;
    server->map.last_updated = gettickselapsed(&server->clock);
    server->map.tiles = malloc(sizeof(tile_t *) * (server->map.size.y + 1));
    if (!server->map.tiles)
        return FAILURE;
    server->map.tiles[server->map.size.y] = NULL;
    for (u_int i = 0; i < server->map.size.y; i++) {
        server->map.tiles[i] =
            malloc(sizeof(tile_t) * (server->map.size.x + 1));
        if (!server->map.tiles[i])
            return FAILURE;
        server->map.tiles[i] =
            set_default_tile(server->map.tiles[i], server->map.size.x);
    }
    randomize_map(server);
    return SUCCESS;
}
