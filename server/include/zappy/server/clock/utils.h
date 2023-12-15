/*
** EPITECH PROJECT, 2023
** clock
** File description:
** utils
*/

#pragma once

#include <zappy/server/infos.h>

int gettickselapsed(zappy_clock_t *);
void update_ticks(server_t *);
int add_ticks_occupied(client_node_t *, int, server_t *);
