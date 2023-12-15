/*
** EPITECH PROJECT, 2023
** client_command
** File description:
** zappy
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>
#include <zappy/server/summon/infos.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static const summons_funptr_t SUMMON[] = {
    {.summon = ZAPPY_MSG, .handler = &msz_func, .type = GUI},
    {.summon = ZAPPY_BCT, .handler = &bct_func, .type = GUI},
    {.summon = ZAPPY_PNW, .handler = &mct_func, .type = GUI},
    {.summon = ZAPPY_TNA, .handler = &tna_func, .type = GUI},
    {.summon = ZAPPY_PPO, .handler = &ppo_func, .type = GUI},
    {.summon = ZAPPY_PLV, .handler = &plv_func, .type = GUI},
    {.summon = ZAPPY_PIN, .handler = &pin_func, .type = GUI},
    {.summon = ZAPPY_SGT, .handler = &sgt_func, .type = GUI},
    {.summon = ZAPPY_SST, .handler = &sst_func, .type = GUI},
    {.summon = ZAPPY_FORWARD, .handler = &forward_func, .type = AI},
    {.summon = ZAPPY_RIGHT, .handler = &right_func, .type = AI},
    {.summon = ZAPPY_LEFT, .handler = &left_func, .type = AI},
    {.summon = ZAPPY_LOOK, .handler = &look_func, .type = AI},
    {.summon = ZAPPY_FORK, .handler = &fork_func, .type = AI},
    {.summon = ZAPPY_INVENTORY, .handler = &inventory_func, .type = AI},
    {.summon = ZAPPY_BROADCAST, .handler = &broadcast_func, .type = AI},
    {.summon = ZAPPY_CONNECT_NBR, .handler = &connect_nbr_func, .type = AI},
    {.summon = ZAPPY_EJECT, .handler = &eject_func, .type = AI},
    {.summon = ZAPPY_TAKE, .handler = &take_func, .type = AI},
    {.summon = ZAPPY_SET, .handler = &set_func, .type = AI},
    {.summon = ZAPPY_INCANTATION, .handler = &incantation_func, .type = AI},
    {0},
};

static int parse_command(char **summon, server_t *server, client_node_t *client)
{
    if (!server || !summon || !(*summon))
        return NOT_FOUND;
    for (int i = 0; SUMMON[i].handler; i += 1) {
        if (strcmp(SUMMON[i].summon, summon[0]) == 0 &&
            SUMMON[i].type == client->state)
            return SUMMON[i].handler(server, summon, client);
    }
    return NOT_FOUND;
}

static void error_command(char **tab, server_t *server, client_node_t *client)
{
    if (tab == NULL || parse_command(tab, server, client) == NOT_FOUND) {
        if (client->state == GUI) {
            dprintf(client->cfd, GUI_UNKNOWN);
            return;
        }
        dprintf(client->cfd, UNKNOWN_COMMAND);
    }
}

int parse_event_client(server_t *server, char *line, client_node_t *client)
{
    char **tab = NULL;

    if (!server || !line || !client)
        return FAILURE;
    if (!(tab = str_to_array(line, SEPARATOR_CMD))) {
        if (client->state == GUI)
            return set_error(client->cfd, GUI_UNKNOWN, false);
        return set_error(client->cfd, UNKNOWN_COMMAND, false);
    }
    error_command(tab, server, client);
    free(line);
    free_array(tab);
    return SUCCESS;
}
