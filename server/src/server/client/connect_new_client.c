/*
** EPITECH PROJECT, 2023
** client
** File description:
** connect_new_client
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/utils.h>

static const inventory_t INVENTORY[] = {
    {.resource = FOOD, .units = 10},     {.resource = LINEMATE, .units = 0},
    {.resource = DERAUMERE, .units = 0}, {.resource = SIBUR, .units = 0},
    {.resource = MENDIANE, .units = 0},  {.resource = PHIRAS, .units = 0},
    {.resource = THYSTAME, .units = 0},  {0},
};

static void set_stats(client_node_t *client)
{
    client->state = NONE;
    client->stats.action.type = NOTHING;
    client->stats.action.ticks = -1;
    client->stats.level = 1;
    client->stats.orientation = rand() % WEST + 1;
    for (unsigned int i = 0; i < INVENTORY_SLOTS; i++) {
        client->stats.inventory[i].resource = INVENTORY[i].resource;
        client->stats.inventory[i].units = INVENTORY[i].units;
    }
    for (u_int i = 0; i < MAX_WAITING_SUMMONS; i++) {
        client->queue[i].size = -1;
        client->queue[i].summon = NULL;
    }
}

int connect_new_client(server_t *server)
{
    client_node_t *new_client = malloc(sizeof(client_node_t));
    int size_addr = sizeof(struct sockaddr_in);

    if (!server || !new_client)
        return FAILURE;
    *new_client = (client_node_t){0};
    if ((new_client->cfd = accept(server->server_fd,
                                (struct sockaddr *)&new_client->socket_infos,
                                (socklen_t *)&size_addr)) < 0)
        return set_error(STDERR_FILENO, "Accepting client", true);
    FD_SET(new_client->cfd, &server->clients_fd);
    if (!(new_client->uuid = generate_uuid()))
        return set_error(new_client->cfd, "Creating unique uuid", true);
    set_stats(new_client);
    add_client_node(new_client, server);
    dprintf(new_client->cfd, CLIENT_CONNECT);
    return SUCCESS;
}
