/*
** EPITECH PROJECT, 2023
** server
** File description:
** create_server
*/

#include <stdlib.h>
#include <string.h>
#include <zappy/config/config.h>
#include <zappy/server.h>

static char **dup_array(const char *const origin[])
{
    char **dest = NULL;
    int i = 0;

    if (!origin)
        return NULL;
    while (origin[i])
        i++;
    if (!(dest = malloc(sizeof(char *) * (i + 1))))
        return NULL;
    for (int y = 0; y < i; y++) {
        if (!(dest[y] = strdup(origin[y])))
            return NULL;
    }
    dest[i] = NULL;
    return dest;
}

int create_default_server(server_t *server, int port)
{
    args_config_t args = {
        .freq = DEFAULT_FREQ,
        .help = false,
        .nb_clients_og = DEFAULT_CLIENTS,
        .port = port,
        .world = (vector2i_t){.x = DEFAULT_WIDTH, .y = DEFAULT_HEIGHT},
        .team_names = dup_array(DEFAULT_TEAMS),
    };

    if (!server)
        return FAILURE;
    update_server_with_args(server, &args);
    return SUCCESS;
}
