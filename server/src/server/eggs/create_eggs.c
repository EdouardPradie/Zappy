/*
** EPITECH PROJECT, 2023
** eggs
** File description:
** create_eggs
*/

#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/map_utils.h>

static int create_eggs_by_team(team_t **team, server_t *server)
{
    if (!((*team)->eggs = malloc(sizeof(egg_t *) * ((*team)->nb_clients + 1))))
        return FAILURE;
    (*team)->eggs[(*team)->nb_clients] = NULL;
    for (u_int i = 0; i < (*team)->nb_clients; i++) {
        if (!((*team)->eggs[i] = malloc(sizeof(egg_t))))
            return FAILURE;
        (*(*team)->eggs[i]) = (egg_t){0};
        (*team)->eggs[i]->team_uuid = (*team)->uuid;
        server->map.last_egg_id += 1;
        (*team)->eggs[i]->nb = server->map.last_egg_id;
        (*team)->eggs[i]->pos.x = rand() % server->map.size.x;
        (*team)->eggs[i]->pos.y = rand() % server->map.size.y;
        add_egg_to_tile(server, (*team)->eggs[i]->pos, (*team)->eggs[i]->nb);
    }
    return SUCCESS;
}

int create_eggs(server_t *server)
{
    if (!server || !server->teams)
        return FAILURE;
    for (u_int i = 0; server->teams[i]; i++) {
        if (create_eggs_by_team(&server->teams[i], server) != SUCCESS)
            return FAILURE;
    }
    return SUCCESS;
}
