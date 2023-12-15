/*
** EPITECH PROJECT, 2023
** summons
** File description:
** pop_summon
*/

#include <unistd.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>

char *pop_summon(client_node_t *client)
{
    char *summon = NULL;
    if (!client || client->queue[0].size < 0)

        return NULL;
    summon = client->queue[0].summon;
    for (unsigned int i = 1; i < MAX_WAITING_SUMMONS; i++) {
        client->queue[i - 1].summon = client->queue[i].summon;
        client->queue[i - 1].size = client->queue[i].size;
    }
    client->queue[MAX_WAITING_SUMMONS - 1].size = -1;
    client->queue[MAX_WAITING_SUMMONS - 1].summon = NULL;
    return summon;
}
