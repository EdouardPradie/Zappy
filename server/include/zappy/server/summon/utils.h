/*
** EPITECH PROJECT, 2023
** server
** File description:
** summons
*/

#pragma once

#include <zappy/server/infos.h>

int add_summon(char *, client_node_t *);
char *pop_summon(client_node_t *);
int get_summon(server_t *, client_node_t *);
int handle_summon(server_t *, int cfd);
int handle_client_summon(char *cmd, client_node_t *client, server_t *server);

int send_toall_guicli(server_t *, char *str, ...);
void dprint_tile(map_t, ssize_t, ssize_t, client_node_t *);

int parse_event_client(server_t *, char *, client_node_t *);

/* AI funptr */
int forward_north(server_t *, client_node_t *);
int forward_south(server_t *, client_node_t *);
int forward_east(server_t *, client_node_t *);
int forward_west(server_t *, client_node_t *);

/* GUI funptr */
int gui_connect_func(server_t *, char *[], client_node_t *);
int msz_func(server_t *, char *[], client_node_t *);
int bct_func(server_t *, char *[], client_node_t *);
int mct_func(server_t *, char *[], client_node_t *);
int tna_func(server_t *, char *[], client_node_t *);
int ppo_func(server_t *, char *[], client_node_t *);
int plv_func(server_t *, char *[], client_node_t *);
int pin_func(server_t *, char *[], client_node_t *);
int sgt_func(server_t *, char *[], client_node_t *);
int sst_func(server_t *, char *[], client_node_t *);

int forward_func(server_t *, char *[], client_node_t *);
int right_func(server_t *, char *[], client_node_t *);
int left_func(server_t *, char *[], client_node_t *);
int look_func(server_t *, char *[], client_node_t *);
int inventory_func(server_t *, char *[], client_node_t *);
int broadcast_func(server_t *, char *[], client_node_t *);
int connect_nbr_func(server_t *, char *[], client_node_t *);
int eject_func(server_t *, char *[], client_node_t *);
int take_func(server_t *, char *[], client_node_t *);
int set_func(server_t *, char *[], client_node_t *);
int incantation_func(server_t *, char *[], client_node_t *);
int fork_func(server_t *, char *[], client_node_t *);
int check_incantation_end(server_t *, client_node_t *, int);
bool loop_clients_level_up(server_t *, client_node_t *);
bool mandatory_resources(server_t *, vector2i_t, int);
char *fill_broadcast_summon(char *args[], char *message);
