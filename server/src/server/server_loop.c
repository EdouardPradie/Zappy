/*
** EPITECH PROJECT, 2023
** server
** File description:
** server_loop
*/

#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/destroy.h>
#include <zappy/server/summon/utils.h>

static void check_if_client_ready(server_t *server, size_t ind, fd_set *clients)
{
    if (FD_ISSET(ind, clients)) {
        if (ind == (size_t)server->server_fd)
            connect_new_client(server);
        else
            handle_summon(server, ind);
    }
}

static void manage_select(server_t *server, fd_set *clients_ready, int ret)
{
    if (!server->running)
        return;
    if (ret < 0) {
        perror("Couldn't select a client ready");
        return;
    }
    if (ret == 0)
        return;
    for (size_t i = 0; i < FD_SETSIZE; i++)
        check_if_client_ready(server, i, clients_ready);
}

int server_loop(server_t *server)
{
    fd_set clients_ready = {0};
    struct timeval val = {0};

    if (!server)
        return FAILURE;
    while (server->running) {
        server = get_server();
        update_ticks(server);
        clients_ready = server->clients_fd;
        manage_select(server, &clients_ready,
                    select(FD_SETSIZE + 1, &clients_ready, NULL, NULL, &val));
        check_game_status(server);
        set_server(server);
    }
    destroy_server(server);
    return SUCCESS;
}
