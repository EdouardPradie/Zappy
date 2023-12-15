/*
** EPITECH PROJECT, 2023
** eggs
** File description:
** find_egg_by_nb
*/

#include <zappy/server.h>

static int is_egg_in_team(team_t *team, int nb)
{
    if (!team->eggs)
        return -1;
    for (u_int i = 0; team->eggs[i]; i++)
        if (team->eggs[i]->nb == nb)
            return i;
    return -1;
}

egg_t **find_egg_by_nb(server_t *server, int nb)
{
    int value = 0;

    if (!server || nb < 0 || !server->teams)
        return NULL;
    for (u_int i = 0; server->teams[i]; i++) {
        if ((value = is_egg_in_team(server->teams[i], nb)) >= 0)
            return server->teams[i]->eggs + value;
    }
    return NULL;
}
