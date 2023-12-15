/*
** EPITECH PROJECT, 2023
** server
** File description:
** map_utils
*/

#pragma once

#include <zappy/server/infos.h>

#define DENSITY_FOOD 0.5
#define DENSITY_LINEMATE 0.3
#define DENSITY_DERAUMERE 0.15
#define DENSITY_SIBUR 0.1
#define DENSITY_MENDIANE 0.1
#define DENSITY_PHIRAS 0.08
#define DENSITY_THYSTAME 0.05

#define UPDATE_TICKS 20

static const double DENSITY_INVENTORY[INVENTORY_SLOTS] = {
    DENSITY_FOOD,     DENSITY_LINEMATE, DENSITY_DERAUMERE, DENSITY_SIBUR,
    DENSITY_MENDIANE, DENSITY_PHIRAS,   DENSITY_THYSTAME,
};

int generate_map(server_t *);
int update_map(server_t *);
bool has_stock_left(const int *);
int stock(vector2i_t, double, int *);
int change_player_pos(server_t *, const char *, vector2i_t, vector2i_t);
bool delete_eggs_from_tile(server_t *, vector2i_t);
int from_egg_to_player_tile(server_t *, client_node_t *, egg_t *);
int add_egg_to_tile(server_t *, vector2i_t, int);
int len_eggs(const int *);
