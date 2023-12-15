/*
** EPITECH PROJECT, 2023
** plv_func
** File description:
** zappy
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

int plv_func(server_t *server, char *args[], client_node_t *client)
{
    client_node_t *tmp = NULL;
    int fd = 0;

    if (!client || !server || !args || array_len(args) != 2)
        return FAILURE;
    tmp = server->clients.head;
    if (!tmp || (fd = atoi(args[1])) <= 0)
        return FAILURE;
    for (u_int ind = 0; ind < server->clients.length; ind++) {
        if (fd == tmp->cfd) {
            dprintf(client->cfd, DISPATCH_PLV, tmp->cfd, tmp->stats.level);
            return SUCCESS;
        }
        tmp = tmp->next;
    }
    return FAILURE;
}
