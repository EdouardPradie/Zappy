/*
** EPITECH PROJECT, 2023
** server
** File description:
** tests_summons_ai
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/destroy.h>
#include <zappy/server/summon/utils.h>

void redirect(void);
int create_default_server(server_t *server, int port);

Test(broadcast_func, broadcast_func)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    client_node_t *client2 = malloc(sizeof(client_node_t));
    client_node_t *client3 = malloc(sizeof(client_node_t));
    char *inv1[] = {"", NULL};
    char *args[] = {"", "food", NULL};

    cr_assert_eq(create_default_server(&server, 4257), SUCCESS);
    add_client_node(client, &server);
    add_client_to_team(client, &server, "Team1");
    add_client_node(client2, &server);
    add_client_to_team(client2, &server, "Team1");
    add_client_node(client3, &server);
    gui_connect_func(&server, NULL, client3);
    client3->state = GUI;
    cr_assert_eq(broadcast_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(broadcast_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(broadcast_func(&server, NULL, client), FAILURE);
    cr_assert_eq(broadcast_func(&server, inv1, client), FAILURE);
    cr_assert_eq(broadcast_func(&server, args, client), SUCCESS);
}

Test(connect_nbr, connect_nbr, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char *inv[] = {"", "", NULL};
    char *args[] = {"args", NULL};

    cr_assert_eq(create_default_server(&server, 4256), SUCCESS);
    client->cfd = STDERR_FILENO;
    add_client_node(client, &server);
    add_client_to_team(client, &server, "Team1");
    cr_assert_eq(connect_nbr_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(connect_nbr_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(connect_nbr_func(&server, NULL, client), FAILURE);
    cr_assert_eq(connect_nbr_func(&server, inv, client), FAILURE);
    client->cfd = STDOUT_FILENO;
    cr_assert_eq(connect_nbr_func(&server, args, client), SUCCESS);
    cr_assert_stdout_eq_str("2\n");
    client->cfd = STDERR_FILENO;
    client->uuid_team = "";
    cr_assert_eq(connect_nbr_func(&server, args, client), FAILURE);
    destroy_server(&server);
}

Test(inventory_func, inventory_func, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char *inv[] = {"", "", NULL};
    char *args[] = {"args", NULL};

    cr_assert_eq(create_default_server(&server, 4257), SUCCESS);
    client->cfd = STDERR_FILENO;
    client->stats.inventory[FOOD].units = 37;
    client->stats.inventory[LINEMATE].units = 36;
    client->stats.inventory[DERAUMERE].units = 35;
    client->stats.inventory[SIBUR].units = 34;
    client->stats.inventory[MENDIANE].units = 33;
    client->stats.inventory[PHIRAS].units = 32;
    client->stats.inventory[THYSTAME].units = 31;
    add_client_node(client, &server);
    add_client_to_team(client, &server, "Team1");
    cr_assert_eq(inventory_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(inventory_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(inventory_func(&server, NULL, client), FAILURE);
    cr_assert_eq(inventory_func(&server, inv, client), FAILURE);
    client->cfd = STDOUT_FILENO;
    cr_assert_eq(inventory_func(&server, args, client), SUCCESS);
    cr_assert_stdout_eq_str("[food 37, linemate 36, deraumere 35, sibur "
                            "34, mendiane 33, phiras "
                            "32, thystame 31]\n");
    destroy_server(&server);
}

Test(forward_func, forward_func, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char *inv[] = {"", "", NULL};
    char *args[] = {"args", NULL};
    vector2i_t pos = {1, 1};

    cr_assert_eq(create_default_server(&server, 4257), SUCCESS);
    add_client_node(client, &server);
    add_client_to_team(client, &server, "Team1");
    client->stats.pos = pos;
    client->stats.orientation = NORTH;
    cr_assert_eq(forward_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(forward_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(forward_func(&server, NULL, client), FAILURE);
    cr_assert_eq(forward_func(&server, inv, client), FAILURE);
    printf("{%zu,%zu}\n", client->stats.pos.x, client->stats.pos.y);
    cr_assert_eq(forward_func(&server, args, client), SUCCESS);
    printf("{%zu,%zu}\n", client->stats.pos.x, client->stats.pos.y);
    cr_assert_eq(client->stats.pos.y, 0);
    cr_assert_eq(forward_func(&server, args, client), SUCCESS);
    cr_assert_eq(client->stats.pos.y, 9);
    client->stats.orientation = SOUTH;
    cr_assert_eq(forward_func(&server, args, client), SUCCESS);
    cr_assert_eq(client->stats.pos.y, 0);
    cr_assert_eq(forward_func(&server, args, client), SUCCESS);
    cr_assert_eq(client->stats.pos.y, 1);
    client->stats.orientation = WEST;
    cr_assert_eq(forward_func(&server, args, client), SUCCESS);
    cr_assert_eq(client->stats.pos.x, 0);
    cr_assert_eq(forward_func(&server, args, client), SUCCESS);
    cr_assert_eq(client->stats.pos.x, 9);
    client->stats.orientation = EAST;
    cr_assert_eq(forward_func(&server, args, client), SUCCESS);
    cr_assert_eq(client->stats.pos.x, 0);
    cr_assert_eq(forward_func(&server, args, client), SUCCESS);
    cr_assert_eq(client->stats.pos.x, 1);
    destroy_server(&server);
}

Test(right_func, right_func, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    vector2i_t pos = {1, 1};

    cr_assert_eq(create_default_server(&server, 4257), SUCCESS);
    add_client_node(client, &server);
    add_client_to_team(client, &server, "Team1");
    client->stats.pos = pos;
    client->stats.orientation = 19;
    cr_assert_eq(right_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(right_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(right_func(&server, NULL, client), FAILURE);
    client->stats.orientation = NORTH;
    cr_assert_eq(right_func(&server, NULL, client), SUCCESS);
    cr_assert_eq(client->stats.orientation, EAST);
    cr_assert_eq(right_func(&server, NULL, client), SUCCESS);
    cr_assert_eq(client->stats.orientation, SOUTH);
    cr_assert_eq(right_func(&server, NULL, client), SUCCESS);
    cr_assert_eq(client->stats.orientation, WEST);
    cr_assert_eq(right_func(&server, NULL, client), SUCCESS);
    cr_assert_eq(client->stats.orientation, NORTH);
    destroy_server(&server);
}

Test(left_func, left_func, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    vector2i_t pos = {1, 1};

    cr_assert_eq(create_default_server(&server, 4257), SUCCESS);
    add_client_node(client, &server);
    add_client_to_team(client, &server, "Team1");
    client->stats.pos = pos;
    client->stats.orientation = 19;
    cr_assert_eq(left_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(left_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(left_func(&server, NULL, client), FAILURE);
    client->stats.orientation = NORTH;
    cr_assert_eq(left_func(&server, NULL, client), SUCCESS);
    cr_assert_eq(client->stats.orientation, WEST);
    cr_assert_eq(left_func(&server, NULL, client), SUCCESS);
    cr_assert_eq(client->stats.orientation, SOUTH);
    cr_assert_eq(left_func(&server, NULL, client), SUCCESS);
    cr_assert_eq(client->stats.orientation, EAST);
    cr_assert_eq(left_func(&server, NULL, client), SUCCESS);
    cr_assert_eq(client->stats.orientation, NORTH);
    destroy_server(&server);
}

Test(set_take_func, set_take_func, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    vector2i_t pos = {1, 1};
    char *inv1[] = {"", NULL};
    char *inv2[] = {"", "mouias", NULL};
    char *args[] = {"", "food", NULL};

    cr_assert_eq(create_default_server(&server, 4257), SUCCESS);
    add_client_node(client, &server);
    add_client_to_team(client, &server, "Team1");
    server.map.tiles[pos.y][pos.x].slots[FOOD].units = 7;
    client->stats.pos = pos;
    cr_assert_eq(take_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(take_func(&server, inv1, NULL), FAILURE);
    cr_assert_eq(take_func(&server, inv1, client), FAILURE);
    cr_assert_eq(take_func(&server, inv2, client), FAILURE);
    cr_assert_eq(take_func(&server, args, client), SUCCESS);
    cr_assert_eq(server.map.tiles[pos.y][pos.x].slots[FOOD].units, 6);
    cr_assert_eq(set_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(set_func(&server, inv1, NULL), FAILURE);
    cr_assert_eq(set_func(&server, inv1, client), FAILURE);
    cr_assert_eq(set_func(&server, inv2, client), FAILURE);
    cr_assert_eq(set_func(&server, args, client), SUCCESS);
    cr_assert_eq(server.map.tiles[pos.y][pos.x].slots[FOOD].units, 7);
}
