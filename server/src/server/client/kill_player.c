/*
** EPITECH PROJECT, 2023
** client
** File description:
** kill_player
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/summon/utils.h>

static void rebase_nodes(server_t *server, client_node_t *client)
{
    server->clients.length -= 1;
    if (server->clients.head == client) {
        server->clients.head = server->clients.head->next;
    }
    client->prev->next = client->next;
    client->next->prev = client->prev;
    if (server->clients.length == 0)
        server->clients.head = NULL;
}

static void send_infos(server_t *server, client_node_t *client, bool alive)
{
    char output[BUFFER_SIZE] = {0};

    sprintf(output, DISPATCH_PDI, client->cfd);
    send_toall_guicli(server, output);
    if (alive)
        dprintf(client->cfd, AI_DEATH);
}

int kill_player(server_t *server, client_node_t *client, bool alive)
{
    if (!server || !client)
        return FAILURE;
    for (u_int i = 0; i < INVENTORY_SLOTS; i++) {
        server->map.current_stocks[i] -= server->map.init_stock[i];
    }
    rebase_nodes(server, client);
    send_infos(server, client, alive);
    delete_client_from_team(client, server);
    free(client->uuid);
    FD_CLR(client->cfd, &server->clients_fd);
    close(client->cfd);
    free(client);
    return SUCCESS;
}
