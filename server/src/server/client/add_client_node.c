/*
** EPITECH PROJECT, 2023
** client
** File description:
** add_client_node
*/

#include <zappy/server.h>
#include <zappy/server/infos.h>

int add_client_node(client_node_t *new_client, server_t *server)
{
    if (!new_client || !server)
        return FAILURE;
    new_client->next = new_client;
    new_client->prev = new_client;
    if (!server->clients.head) {
        server->clients.head = new_client;
    } else {
        new_client->prev = server->clients.head->prev;
        new_client->next = server->clients.head;
        server->clients.head->prev->next = new_client;
        server->clients.head->prev = new_client;
    }
    server->clients.length++;
    return SUCCESS;
}
