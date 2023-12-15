/*
** EPITECH PROJECT, 2023
** summons
** File description:
** handle_summon
*/

#include <stdlib.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static int set_client_state(char *cmd, client_node_t *client, server_t *server)
{
    char **tab = NULL;
    int status = 0;

    if (!server || !cmd || !client)
        return FAILURE;
    if (!(tab = str_to_array(cmd, SEPARATOR_CMD)))
        return set_error(client->cfd, UNKNOWN_COMMAND, false);
    if (strcmp(tab[0], ZAPPY_GUI_CONNECT) == SUCCESS)
        status = gui_connect_func(server, tab, client);
    else
        status = add_client_to_team(client, server, tab[0]);
    free_array(tab);
    free(cmd);
    return status;
}

int handle_client_summon(char *cmd, client_node_t *client, server_t *server)
{
    if (!cmd)
        return SUCCESS;
    if (client->state == NONE)
        return set_client_state(cmd, client, server);
    return parse_event_client(server, cmd, client);
}

int handle_summon(server_t *server, int cfd)
{
    client_node_t *client = NULL;

    if (!server || cfd <= 0 || !(client = find_client_by_fd(cfd, server)))
        return FAILURE;
    if (get_summon(server, client) != SUCCESS)
        return FAILURE;
    return SUCCESS;
}
