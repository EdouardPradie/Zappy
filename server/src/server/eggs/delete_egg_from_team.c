/*
** EPITECH PROJECT, 2023
** eggs
** File description:
** delete_egg_from_team
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

static void send_infos(server_t *server, int egg)
{
    char output[BUFFER_SIZE] = {0};

    sprintf(output, DISPATCH_EDI, egg);
    send_toall_guicli(server, output);
}

static egg_t **delete_from_egg_array(egg_t **src, u_int ind)
{
    ssize_t size = 0;
    egg_t **dest = NULL;
    int flag = 0;

    if (!src || (size = array_len(src)) < ind)
        return src;
    if (size <= 1 || !(dest = malloc(sizeof(egg_t *) * (size)))) {
        free(src);
        return NULL;
    }
    dest[size - 1] = NULL;
    for (u_int i = 0; i < size - 1; i++) {
        if (i == ind)
            flag = 1;
        dest[i] = src[i + flag];
    }
    free(src);
    return dest;
}

static int check_team_eggs(server_t *server, int id, u_int ind)
{
    int flag = 0;
    team_t **teams = server->teams;

    if (!teams[ind]->eggs)
        return FAILURE;
    for (u_int i = 0; teams[ind]->eggs[i]; i++) {
        if (teams[ind]->eggs[i]->nb == id) {
            send_infos(server, teams[ind]->eggs[i]->nb);
            teams[ind]->eggs = delete_from_egg_array(teams[ind]->eggs, i);
            teams[ind]->spots_free--;
            flag = 1;
            break;
        }
    }
    if (flag && teams[ind]->eggs)
        return SUCCESS;
    return FAILURE;
}

int delete_egg_from_team(server_t *server, int id)
{
    if (!server || id < 0)
        return FAILURE;
    for (u_int i = 0; server->teams[i]; i++)
        if (check_team_eggs(server, id, i) == SUCCESS)
            return SUCCESS;
    return FAILURE;
}
