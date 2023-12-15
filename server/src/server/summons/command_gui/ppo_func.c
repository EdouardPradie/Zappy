/*
** EPITECH PROJECT, 2023
** ppo_func
** File description:
** zappy
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

int ppo_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = NULL;
    int client_nb = 0;

    if (!args || array_len(args) != 2 || !server || !client)
        return FAILURE;
    client_nb = atoi(args[1]);
    tmp = server->clients.head;
    if (!tmp || client_nb <= 0 || !strisnum(args[1]))
        return FAILURE;
    for (u_int ind = 0; ind < server->clients.length; ind++) {
        if (client_nb == tmp->cfd) {
            dprintf(client->cfd, DISPATCH_PPO, tmp->cfd, tmp->stats.pos.x,
                    tmp->stats.pos.y, tmp->stats.orientation);
            return SUCCESS;
        }
        tmp = tmp->next;
    }
    return FAILURE;
}
