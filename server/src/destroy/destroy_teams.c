/*
** EPITECH PROJECT, 2023
** destroy
** File description:
** destroy_teams
*/

#include <stdlib.h>
#include <zappy/server/destroy.h>

static void free_eggs(egg_t **eggs)
{
    if (!eggs)
        return;
    for (u_int i = 0; eggs[i]; i++)
        free(eggs[i]);
    free(eggs);
}

void destroy_teams(team_t **teams)
{
    if (!teams || !(*teams))
        return;
    for (u_int i = 0; teams[i]; i++) {
        free(teams[i]->uuid);
        free(teams[i]->uuid_clients);
        free(teams[i]->team_name);
        free_eggs(teams[i]->eggs);
        free(teams[i]);
    }
    free(teams);
}
