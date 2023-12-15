/*
** EPITECH PROJECT, 2023
** client
** File description:
** starve_players
*/

#include <zappy/server.h>
#include <zappy/server/client.h>

int starve_players(server_t *server)
{
    client_node_t *tmp = NULL;

    if (!server || !(tmp = server->clients.head))
        return FAILURE;
    for (u_int ind = 0; ind < server->clients.length; ind++) {
        if (tmp->state != AI) {
            tmp = tmp->next;
            continue;
        }
        tmp->stats.inventory[FOOD].units -= 1;
        if (tmp->stats.inventory[FOOD].units < 0) {
            tmp = tmp->next;
            kill_player(server, tmp->prev, true);
            continue;
        }
        tmp = tmp->next;
    }
    return SUCCESS;
}
