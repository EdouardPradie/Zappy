/*
** EPITECH PROJECT, 2023
** summons
** File description:
** get_summon
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static int client_exists(server_t *server, client_node_t *client)
{
    if (fcntl(client->cfd, F_GETFD) <= 0) {
        if (client->state == AI)
            kill_player(server, client, false);
        else
            destroy_client(server, client);
        return FAILURE;
    }
    return set_error(client->cfd, INVALID_ACTION, false);
}

int get_summon(server_t *server, client_node_t *client)
{
    char *summon = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    int size = 0;

    if (!server || !client)
        return FAILURE;
    memset(summon, '\0', BUFFER_SIZE);
    if ((size = read(client->cfd, summon, BUFFER_SIZE)) <= 0) {
        free(summon);
        return client_exists(server, client);
    }
    summon[size - 1] = '\0';
    if (add_summon(summon, client) != SUCCESS)
        free(summon);
    return SUCCESS;
}
