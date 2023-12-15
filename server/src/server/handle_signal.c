/*
** EPITECH PROJECT, 2023
** server
** File description:
** handle_signal
*/

#include <unistd.h>
#include <zappy/server.h>
#include <zappy/server/infos.h>

server_t *get_server(void)
{
    static server_t server = {0};

    return &server;
}

void set_server(server_t *server)
{
    server_t *to_change = get_server();

    *to_change = *server;
}

void handle_sigint(int __attribute__((unused)) sigf)
{
    server_t *server = get_server();

    close(server->server_fd);
    server->running = false;
}
