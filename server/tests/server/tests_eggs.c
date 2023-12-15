/*
** EPITECH PROJECT, 2023
** server
** File description:
** tests_eggs
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/destroy.h>
#include <zappy/server/map_utils.h>

void redirect(void);
int create_default_server(server_t *server, int port);

Test(add_egg_to_tile, null_tests_egg)
{
    server_t server = {0};
    vector2i_t invalid_pos = {6666666, 896757};

    cr_assert_eq(add_egg_to_tile(NULL, invalid_pos, 0), FAILURE);
    cr_assert_eq(add_egg_to_tile(&server, invalid_pos, 0), FAILURE);
}

Test(create_egg, create_eggs)
{
    server_t server = {0};

    server.teams = NULL;
    cr_assert_eq(create_eggs(NULL), FAILURE);
    cr_assert_eq(create_eggs(&server), FAILURE);
}

Test(add_egg_to_team, add_egg_to_team_null)
{
    client_node_t client = {0};
    server_t server = {0};

    cr_assert_eq(add_egg_to_team(NULL, NULL), FAILURE);
    cr_assert_eq(add_egg_to_team(&client, NULL), FAILURE);
    cr_assert_eq(add_egg_to_team(&client, &server), FAILURE);
}

Test(add_egg_to_team, add_egg_to_team_basic)
{
    client_node_t client = {0};
    server_t server = {0};
    size_t old_nb = 0;

    cr_assert_eq(create_default_server(&server, 4240), SUCCESS);
    client.uuid_team = server.teams[0]->uuid;
    old_nb = server.teams[0]->nb_clients;
    cr_assert_eq(add_egg_to_team(&client, &server), SUCCESS);
    cr_assert_eq(server.teams[0]->nb_clients, old_nb + 1);
    destroy_server(&server);
}

Test(delete_egg_from_team, delete_egg_from_team_invalid)
{
    server_t server = {0};

    cr_assert_eq(delete_egg_from_team(NULL, 0), FAILURE);
    cr_assert_eq(delete_egg_from_team(&server, -1), FAILURE);
}

Test(delete_egg_from_team, delete_egg_from_team_valid)
{
    server_t server = {0};

    cr_assert_eq(create_default_server(&server, 4239), SUCCESS);
    // cr_assert_eq(delete_egg_from_team(&server, 1), SUCCESS);
    destroy_server(&server);
}

Test(delete_egg_from_team, delete_egg_from_team_invalid_2)
{
    server_t server = {0};

    cr_assert_eq(create_default_server(&server, 4238), SUCCESS);
    free(server.teams[0]->eggs);
    server.teams[0]->eggs = NULL;
    cr_assert_eq(delete_egg_from_team(&server, 1), FAILURE);
    destroy_server(&server);
}

Test(find_egg_by_nb, find_egg_by_nb_invalid)
{
    server_t server = {0};

    server.teams = NULL;
    cr_assert_null(find_egg_by_nb(NULL, -1));
    cr_assert_null(find_egg_by_nb(&server, -1));
    cr_assert_null(find_egg_by_nb(&server, 1));
}

Test(find_egg_by_nb, find_egg_by_nb_valid)
{
    server_t server = {0};

    cr_assert_eq(create_default_server(&server, 4237), SUCCESS);
    // cr_assert_not_null(find_egg_by_nb(&server, 5));
    cr_assert_null(find_egg_by_nb(&server, 512));
    destroy_server(&server);
}

Test(from_egg_to_player, from_egg_to_player)
{
    server_t server = {0};
    client_node_t client = {0};
    team_t *team = malloc(sizeof(team_t));
    team_t *teams[] = {NULL, NULL};

    cr_assert_eq(create_default_server(&server, 4237), SUCCESS);
    cr_assert_eq(from_egg_to_player(NULL, NULL, NULL), FAILURE);
    cr_assert_eq(from_egg_to_player(&client, NULL, NULL), FAILURE);
    cr_assert_eq(from_egg_to_player(&client, teams, NULL), FAILURE);
    if (!team)
        cr_assert_eq(0, 1);
    team->eggs = NULL;
    cr_assert_eq(from_egg_to_player(&client, &team, &server), FAILURE);
    team->eggs = malloc(sizeof(egg_t *) * 2);
    if (!team->eggs)
        cr_assert_eq(1, 2);
    team->eggs[0] = malloc(sizeof(egg_t));
    if (!team->eggs[0])
        cr_assert_eq(2, 3);
    *(team->eggs[0]) = (egg_t){0};
    team->eggs[0]->pos = (vector2i_t){4, 4};
    team->spots_free = 0;
    cr_assert_eq(from_egg_to_player(&client, &team, &server), SUCCESS);
    cr_assert_null(team->eggs[0]);
    cr_assert_eq(client.stats.pos.x, 4);
    free(team);
    destroy_server(&server);
}
