/*
** EPITECH PROJECT, 2023
** server
** File description:
** tests_misc
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <zappy/server.h>

void redirect(void);

Test(handle_signal, handle_signal)
{
    server_t server = {0};

    server.server_fd = open("./tmp", O_CREAT | O_TRUNC | O_RDWR);
    cr_assert_neq(server.server_fd, -1);
    handle_sigint(2);
    cr_assert_leq(fcntl(server.server_fd, F_GETFD), 0);
    cr_assert_eq(server.running, false);
    remove("./tmp");
    set_server(&server);
}
