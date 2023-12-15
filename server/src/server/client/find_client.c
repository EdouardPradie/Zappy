/*
** EPITECH PROJECT, 2023
** client
** File description:
** find_client
*/

#include <stddef.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>

client_node_t *find_client_by_fd(int fd, server_t *server)
{
    client_node_t *to_find = 0;

    if (!server || !(to_find = server->clients.head))
        return NULL;
    for (size_t ind = 0; ind < server->clients.length; ind++) {
        if (to_find->cfd == fd)
            return to_find;
        to_find = to_find->next;
    }
    return NULL;
}

client_node_t *find_client_by_uuid(const char *const uuid, server_t *server)
{
    client_node_t *to_find = 0;

    if (!server || !uuid || !(to_find = server->clients.head))
        return NULL;
    for (size_t ind = 0; ind < server->clients.length; ind++) {
        if (strcmp(to_find->uuid, uuid) == SUCCESS)
            return to_find;
        to_find = to_find->next;
    }
    return NULL;
}
