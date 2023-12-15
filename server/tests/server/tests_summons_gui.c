/*
** EPITECH PROJECT, 2023
** server
** File description:
** tests_summons_gui
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <unistd.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/destroy.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

void redirect(void);
int create_default_server(server_t *server, int port);

Test(bct_func, bct_func, .init = redirect)
{
    char *args[] = {"bct", "1", "5"};
    char *inv1[] = {NULL};
    char *inv2[] = {"bct", "-1", "5"};
    char *inv3[] = {"bct", "1", "-5"};
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char output[4096] = {0};

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    client->uuid = generate_uuid();
    client->cfd = STDOUT_FILENO;
    cr_assert_eq(bct_func(&server, NULL, client), FAILURE);
    cr_assert_eq(bct_func(&server, inv1, client), FAILURE);
    cr_assert_eq(bct_func(NULL, args, client), FAILURE);
    cr_assert_eq(bct_func(&server, args, NULL), FAILURE);
    cr_assert_eq(bct_func(&server, inv2, client), FAILURE);
    cr_assert_eq(bct_func(&server, inv3, client), FAILURE);
    cr_assert_eq(bct_func(&server, args, client), SUCCESS);
    sprintf(output, DISPATCH_BCT, (ssize_t)1, (ssize_t)5,
            server.map.tiles[5][1].slots[FOOD].units,
            server.map.tiles[5][1].slots[LINEMATE].units,
            server.map.tiles[5][1].slots[DERAUMERE].units,
            server.map.tiles[5][1].slots[SIBUR].units,
            server.map.tiles[5][1].slots[MENDIANE].units,
            server.map.tiles[5][1].slots[PHIRAS].units,
            server.map.tiles[5][1].slots[THYSTAME].units);
    cr_assert_stdout_eq_str(output);
    destroy_server(&server);
}

Test(msz_func, msz_func, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char output[4096] = {0};

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    client->uuid = generate_uuid();
    client->cfd = STDOUT_FILENO;
    sprintf(output, DISPATCH_MSZ, server.map.size.x, server.map.size.y);
    cr_assert_eq(msz_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(msz_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(msz_func(&server, NULL, client), SUCCESS);
    cr_assert_stdout_eq_str(output);
    destroy_server(&server);
}

Test(mct_func, mct_func, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char output[4096] = {0};
    int size = 0;

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    client->cfd = STDOUT_FILENO;
    for (ssize_t y = 0; (size_t)y < server.map.size.y; y++) {
        for (ssize_t x = 0; (size_t)x < server.map.size.x; x++) {
            size += sprintf(output + size, DISPATCH_BCT, x, y,
                            server.map.tiles[y][x].slots[FOOD].units,
                            server.map.tiles[y][x].slots[LINEMATE].units,
                            server.map.tiles[y][x].slots[DERAUMERE].units,
                            server.map.tiles[y][x].slots[SIBUR].units,
                            server.map.tiles[y][x].slots[MENDIANE].units,
                            server.map.tiles[y][x].slots[PHIRAS].units,
                            server.map.tiles[y][x].slots[THYSTAME].units);
        }
    }
    cr_assert_eq(mct_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(mct_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(mct_func(&server, NULL, client), SUCCESS);
    cr_assert_stdout_eq_str(output);
    destroy_server(&server);
}

Test(tna_func, tna_func, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char output[4096] = {0};

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    client->cfd = STDOUT_FILENO;
    sprintf(output, "tna Team1\ntna Team2\ntna Team3\ntna Team4\n");
    cr_assert_eq(tna_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(tna_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(tna_func(&server, NULL, client), SUCCESS);
    cr_assert_stdout_eq_str(output);
    destroy_server(&server);
}

Test(sst_func, sst_func, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char output[4096] = {0};
    char *inv1[] = {NULL};
    char *inv2[] = {"a", "-6", NULL};
    char *inv3[] = {"a", "a", NULL};
    char *args[] = {"a", "10", NULL};

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    client->cfd = STDOUT_FILENO;
    sprintf(output, DISPATCH_SST, 10);
    cr_assert_eq(sst_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(sst_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(sst_func(&server, NULL, client), FAILURE);
    cr_assert_eq(sst_func(&server, inv1, client), FAILURE);
    cr_assert_eq(sst_func(&server, inv2, client), FAILURE);
    cr_assert_eq(sst_func(&server, inv3, client), FAILURE);
    cr_assert_eq(sst_func(&server, args, client), SUCCESS);
    cr_assert_stdout_eq_str(output);
    destroy_server(&server);
}

Test(pin_func, pin_func, .init = redirect)
{
    char *inv1[] = {NULL};
    char *inv2[] = {"a", "-6", NULL};
    char *inv3[] = {"a", "a", NULL};
    char *inv4[] = {"a", "6", NULL};
    char *args[] = {"a", "1", NULL};
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char output[4096] = {0};

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    client->cfd = STDOUT_FILENO;
    sprintf(output, DISPATCH_PIN, client->cfd, client->stats.pos.x,
            client->stats.pos.y, client->stats.inventory[FOOD].units,
            client->stats.inventory[LINEMATE].units,
            client->stats.inventory[DERAUMERE].units,
            client->stats.inventory[SIBUR].units,
            client->stats.inventory[MENDIANE].units,
            client->stats.inventory[PHIRAS].units,
            client->stats.inventory[THYSTAME].units);
    cr_assert_eq(pin_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(pin_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(pin_func(&server, NULL, client), FAILURE);
    cr_assert_eq(pin_func(&server, inv1, client), FAILURE);
    cr_assert_eq(pin_func(&server, inv2, client), FAILURE);
    cr_assert_eq(pin_func(&server, inv3, client), FAILURE);
    cr_assert_eq(pin_func(&server, args, client), FAILURE);
    add_client_node(client, &server);
    cr_assert_eq(pin_func(&server, inv2, client), FAILURE);
    cr_assert_eq(pin_func(&server, inv4, client), FAILURE);
    cr_assert_eq(pin_func(&server, args, client), SUCCESS);
    cr_assert_stdout_eq_str(output);
    destroy_server(&server);
}

Test(plv_func, plv_func, .init = redirect)
{
    char *inv1[] = {NULL};
    char *inv2[] = {"a", "-6", NULL};
    char *inv3[] = {"a", "a", NULL};
    char *inv4[] = {"a", "6", NULL};
    char *args[] = {"a", "1", NULL};
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char output[4096] = {0};

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    client->cfd = STDOUT_FILENO;
    sprintf(output, DISPATCH_PLV, client->cfd, client->stats.level);
    cr_assert_eq(plv_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(plv_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(plv_func(&server, NULL, client), FAILURE);
    cr_assert_eq(plv_func(&server, inv1, client), FAILURE);
    cr_assert_eq(plv_func(&server, inv2, client), FAILURE);
    cr_assert_eq(plv_func(&server, inv3, client), FAILURE);
    cr_assert_eq(plv_func(&server, args, client), FAILURE);
    add_client_node(client, &server);
    cr_assert_eq(plv_func(&server, inv2, client), FAILURE);
    cr_assert_eq(plv_func(&server, inv4, client), FAILURE);
    cr_assert_eq(plv_func(&server, args, client), SUCCESS);
    cr_assert_stdout_eq_str(output);
    destroy_server(&server);
}

Test(ppo_func, ppo_func, .init = redirect)
{
    char *inv1[] = {NULL};
    char *inv2[] = {"a", "-6", NULL};
    char *inv3[] = {"a", "a", NULL};
    char *inv4[] = {"a", "6", NULL};
    char *args[] = {"a", "1", NULL};
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char output[4096] = {0};

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    client->cfd = STDOUT_FILENO;
    client->stats.pos = (vector2i_t){5, 5};
    client->stats.orientation = WEST;
    sprintf(output, DISPATCH_PPO, client->cfd, client->stats.pos.x,
            client->stats.pos.y, client->stats.orientation);
    cr_assert_eq(ppo_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(ppo_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(ppo_func(&server, NULL, client), FAILURE);
    cr_assert_eq(ppo_func(&server, inv1, client), FAILURE);
    cr_assert_eq(ppo_func(&server, inv2, client), FAILURE);
    cr_assert_eq(ppo_func(&server, inv3, client), FAILURE);
    cr_assert_eq(ppo_func(&server, args, client), FAILURE);
    add_client_node(client, &server);
    cr_assert_eq(ppo_func(&server, inv2, client), FAILURE);
    cr_assert_eq(ppo_func(&server, inv4, client), FAILURE);
    cr_assert_eq(ppo_func(&server, args, client), SUCCESS);
    cr_assert_stdout_eq_str(output);
    destroy_server(&server);
}

Test(sgt_func, sgt_func, .init = redirect)
{
    server_t server = {0};
    client_node_t client = {0};
    char output[BUFFER_SIZE] = {0};

    client.cfd = STDOUT_FILENO;
    sprintf(output, DISPATCH_SGT, server.clock.freq);
    cr_assert_eq(sgt_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(sgt_func(NULL, NULL, &client), FAILURE);
    cr_assert_eq(sgt_func(&server, NULL, &client), SUCCESS);
    cr_assert_stdout_eq_str(output);
}

Test(gui_connect_func, without_clients, .init = redirect)
{
    server_t server = {0};
    client_node_t client = {0};
    char output[BUFFER_SIZE] = {0};
    int size = 0;
    char *args[] = {"", NULL};

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    client.cfd = STDOUT_FILENO;
    size += sprintf(output, DISPATCH_MSZ, server.map.size.x, server.map.size.y);
    size += sprintf(output + size, DISPATCH_SGT, server.clock.freq);
    for (ssize_t y = 0; (size_t)y < server.map.size.y; y++) {
        for (ssize_t x = 0; (size_t)x < server.map.size.x; x++) {
            size += sprintf(output + size, DISPATCH_BCT, x, y,
                            server.map.tiles[y][x].slots[FOOD].units,
                            server.map.tiles[y][x].slots[LINEMATE].units,
                            server.map.tiles[y][x].slots[DERAUMERE].units,
                            server.map.tiles[y][x].slots[SIBUR].units,
                            server.map.tiles[y][x].slots[MENDIANE].units,
                            server.map.tiles[y][x].slots[PHIRAS].units,
                            server.map.tiles[y][x].slots[THYSTAME].units);
        }
    }
    size +=
        sprintf(output + size, "tna Team1\ntna Team2\ntna Team3\ntna Team4\n");
    cr_assert_eq(gui_connect_func(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(gui_connect_func(&server, NULL, NULL), FAILURE);
    cr_assert_eq(gui_connect_func(&server, args, NULL), FAILURE);
    cr_assert_eq(gui_connect_func(&server, args, &client), SUCCESS);
    // cr_assert_stdout_eq_str(output);
    destroy_server(&server);
}

Test(gui_connect_func, with_clients, .init = redirect)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));
    char output[BUFFER_SIZE] = {0};
    int size = 0;
    char *args[] = {"", NULL};

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    client->cfd = STDOUT_FILENO;
    client->state = AI;
    add_client_node(client, &server);
    add_client_to_team(client, &server, "Team1");
    size += sprintf(output, "2\n10 10\n");
    size += sprintf(output + size, DISPATCH_MSZ, server.map.size.x,
                    server.map.size.y);
    size += sprintf(output + size, DISPATCH_SGT, server.clock.freq);
    for (ssize_t y = 0; (size_t)y < server.map.size.y; y++) {
        for (ssize_t x = 0; (size_t)x < server.map.size.x; x++) {
            size += sprintf(output + size, DISPATCH_BCT, x, y,
                            server.map.tiles[y][x].slots[FOOD].units,
                            server.map.tiles[y][x].slots[LINEMATE].units,
                            server.map.tiles[y][x].slots[DERAUMERE].units,
                            server.map.tiles[y][x].slots[SIBUR].units,
                            server.map.tiles[y][x].slots[MENDIANE].units,
                            server.map.tiles[y][x].slots[PHIRAS].units,
                            server.map.tiles[y][x].slots[THYSTAME].units);
        }
    }
    size +=
        sprintf(output + size, "tna Team1\ntna Team2\ntna Team3\ntna Team4\n");
    size +=
        sprintf(output + size, DISPATCH_PNW, client->cfd, client->stats.pos.x,
                client->stats.pos.y, client->stats.orientation,
                client->stats.level, server.teams[0]->team_name);
    cr_assert_eq(gui_connect_func(&server, args, client), SUCCESS);
    cr_assert_stdout_eq_str(output);
    destroy_server(&server);
}
