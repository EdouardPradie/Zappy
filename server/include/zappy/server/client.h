/*
** EPITECH PROJECT, 2023
** server
** File description:
** client
*/

#pragma once

#include <zappy/server/infos.h>

#define INIT_FOOD 10

// exclusively related to client
int add_client_node(client_node_t *, server_t *);
client_node_t *find_client_by_uuid(const char *, server_t *);
client_node_t *find_client_by_fd(int fd, server_t *);
int connect_new_client(server_t *);
int kill_player(server_t *, client_node_t *, bool);
int starve_players(server_t *);
void destroy_client(server_t *, client_node_t *);

// team related
int add_client_to_team(client_node_t *, server_t *, const char *);
int find_team_by_name(const char *name, server_t *server);
int find_team_by_uuid(const char *, server_t *);
void delete_client_from_team(client_node_t *, server_t *);

// egg related
int create_eggs(server_t *);
int from_egg_to_player(client_node_t *, team_t **, server_t *);
int add_egg_to_team(client_node_t *, server_t *);
int delete_egg_from_team(server_t *, int);
egg_t **find_egg_by_nb(server_t *, int);
