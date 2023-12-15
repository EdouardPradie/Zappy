/*
** EPITECH PROJECT, 2023
** client
** File description:
** find_team
*/

#include <string.h>
#include <zappy/server.h>

int find_team_by_uuid(const char *uuid, server_t *server)
{
    if (!uuid || !server || !server->teams)
        return -1;
    for (unsigned int i = 0; server->teams[i]; i++) {
        if (strcmp(uuid, server->teams[i]->uuid) == SUCCESS)
            return i;
    }
    return -1;
}

int find_team_by_name(const char *name, server_t *server)
{
    if (!name || !server || !server->teams)
        return -1;
    for (unsigned int i = 0; server->teams[i]; i++) {
        if (strcmp(name, server->teams[i]->team_name) == SUCCESS)
            return i;
    }
    return -1;
}
