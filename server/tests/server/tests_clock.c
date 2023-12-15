/*
** EPITECH PROJECT, 2023
** server
** File description:
** tests_clock
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <zappy/server.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/destroy.h>

void redirect(void);
int create_default_server(server_t *server, int port);

Test(gettickselapsed, clock)
{
    server_t server = {0};

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    cr_assert_eq(gettickselapsed(NULL), -1);
    cr_assert_neq(gettickselapsed(&server.clock), -1);
    destroy_server(&server);
}

Test(add_ticks_occupied, add_ticks_occupied)
{
    server_t server = {0};
    client_node_t client = {0};

    cr_assert_eq(add_ticks_occupied(NULL, 0, NULL), FAILURE);
    cr_assert_eq(add_ticks_occupied(NULL, 0, NULL), FAILURE);
    cr_assert_eq(add_ticks_occupied(&client, 0, NULL), FAILURE);
    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    cr_assert_eq(client.stats.action.type, NOTHING);
    cr_assert_eq(add_ticks_occupied(&client, 0, &server), SUCCESS);
    cr_assert_eq(client.stats.action.type, ACTION);
    cr_assert_geq(client.stats.action.ticks, gettickselapsed(&server.clock));
    destroy_server(&server);
}
