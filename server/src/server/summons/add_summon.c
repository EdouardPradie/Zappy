/*
** EPITECH PROJECT, 2023
** summons
** File description:
** add_summon
*/

#include <stdio.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>

int add_summon(char *summon, client_node_t *client)
{
    unsigned int ind = 0;

    if (!summon || !client)
        return FAILURE;
    while (ind < MAX_WAITING_SUMMONS && client->queue[ind].size > -1)
        ind++;
    if (ind >= MAX_WAITING_SUMMONS)
        return FAILURE;
    client->queue[ind].size = strlen(summon);
    client->queue[ind].summon = summon;
    return SUCCESS;
}
