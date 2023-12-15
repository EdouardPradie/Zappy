/*
** EPITECH PROJECT, 2023
** destroy
** File description:
** destroy_clients
*/

#include <stdlib.h>
#include <zappy/server/client.h>
#include <zappy/server/destroy.h>

void destroy_clients(clients_t *clients, server_t *server)
{
    client_node_t *client = NULL;
    client_node_t *anchor = NULL;

    if (!clients)
        return;
    anchor = clients->head;
    client = clients->head;
    for (u_int i = 0; i < clients->length; i++) {
        anchor = anchor->next;
        destroy_client(server, client);
        client = anchor;
    }
}
