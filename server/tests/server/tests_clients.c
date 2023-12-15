/*
** EPITECH PROJECT, 2023
** server
** File description:
** tests_clients
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/destroy.h>
#include <zappy/server/summon/utils.h>
#include <zappy/server/utils.h>

void redirect(void);
int create_default_server(server_t *server, int port);

Test(add_client_node, add_client_node)
{
    server_t server = {0};
    client_node_t client = {0};
    client_node_t next_client = {0};

    client.next = &client;
    client.prev = &client;
    cr_assert_eq(add_client_node(NULL, NULL), FAILURE);
    cr_assert_eq(add_client_node(&client, &server), SUCCESS);
    cr_assert_eq(add_client_node(&next_client, &server), SUCCESS);
    cr_assert_eq(&client, server.clients.head);
}

Test(find_client_by_uuid, find_client_by_uuid)
{
    server_t server = {0};
    client_node_t client = {0};

    client.uuid = "ouep";
    cr_assert_null(find_client_by_uuid(NULL, NULL));
    cr_assert_null(find_client_by_uuid("gné", NULL));
    cr_assert_null(find_client_by_uuid("gné", &server));
    cr_assert_eq(add_client_node(&client, &server), SUCCESS);
    cr_assert_null(find_client_by_uuid("gné", &server));
    cr_assert_not_null(find_client_by_uuid("ouep", &server));
}

Test(find_client_by_fd, find_client_by_fd)
{
    server_t server = {0};
    client_node_t client = {0};

    client.cfd = 7;
    cr_assert_null(find_client_by_fd(-1, NULL));
    cr_assert_null(find_client_by_fd(-1, NULL));
    cr_assert_null(find_client_by_fd(-1, &server));
    cr_assert_eq(add_client_node(&client, &server), SUCCESS);
    cr_assert_null(find_client_by_fd(-1, &server));
    cr_assert_not_null(find_client_by_fd(7, &server));
}

Test(connect_new_client, connect_new_client)
{
    cr_assert_eq(connect_new_client(NULL), FAILURE);
}

Test(kill_player, kill_player)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));

    cr_assert_eq(kill_player(NULL, NULL, false), FAILURE);
    cr_assert_eq(kill_player(&server, NULL, false), FAILURE);
    cr_assert_eq(create_default_server(&server, 4241), SUCCESS);
    client->cfd = open("./tmp", O_CREAT | O_TRUNC | O_RDWR);
    cr_assert_eq(add_client_node(client, &server), SUCCESS);
    cr_assert_eq(kill_player(&server, client, false), SUCCESS);
    cr_assert_null(server.clients.head);
    remove("./tmp");
    destroy_server(&server);
}

Test(starve_players, starve_players_invalid)
{
    server_t server = {0};

    cr_assert_eq(starve_players(NULL), FAILURE);
    cr_assert_eq(starve_players(&server), FAILURE);
}

Test(starve_players, starve_players)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));

    cr_assert_eq(create_default_server(&server, 4243), SUCCESS);
    client->cfd = open("./tmp", O_CREAT | O_TRUNC | O_RDWR);
    cr_assert_eq(add_client_node(client, &server), SUCCESS);
    cr_assert_eq(starve_players(&server), SUCCESS);
    client->stats.inventory[FOOD].units = 1;
    client->state = AI;
    cr_assert_eq(starve_players(&server), SUCCESS);
    cr_assert_eq(client->stats.inventory[FOOD].units, 0);
    cr_assert_eq(starve_players(&server), SUCCESS);
    cr_assert_null(server.clients.head);
    remove("./tmp");
    destroy_server(&server);
}

Test(destroy_client, destroy_client)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));

    cr_assert_eq(create_default_server(&server, 4243), SUCCESS);
    client->uuid = generate_uuid();
    client->cfd = open("./tmp", O_CREAT | O_TRUNC | O_RDWR);
    add_summon(strdup("ouiii"), client);
    cr_assert_eq(add_client_node(client, &server), SUCCESS);
    destroy_client(NULL, NULL);
    destroy_client(NULL, client);
    destroy_client(&server, client);
    remove("./tmp");
    destroy_server(&server);
}

Test(delete_client_from_team, delete_client_from_team)
{
    server_t server = {0};
    client_node_t *client = malloc(sizeof(client_node_t));

    cr_assert_eq(create_default_server(&server, 4244), SUCCESS);
    client->uuid = generate_uuid();
    client->cfd = open("./tmp", O_CREAT | O_TRUNC | O_RDWR);
    add_summon(strdup("ouiii"), client);
    cr_assert_eq(add_client_node(client, &server), SUCCESS);
    delete_client_from_team(NULL, &server);
    delete_client_from_team(client, &server);
    delete_client_from_team(client, NULL);
    add_client_to_team(client, &server, "Team1");
    cr_assert_not_null(server.teams[0]->uuid_clients);
    cr_assert_not_null(server.teams[0]->uuid_clients[0]);
    delete_client_from_team(client, &server);
    cr_assert_null(server.teams[0]->uuid_clients[0]);
    remove("./tmp");
    destroy_server(&server);
}

Test(find_team, find_team)
{
    server_t server = {0};

    cr_assert_eq(create_default_server(&server, 4245), SUCCESS);
    cr_assert_eq(find_team_by_uuid(NULL, &server), -1);
    cr_assert_eq(find_team_by_uuid(server.teams[1]->uuid, NULL), -1);
    cr_assert_eq(find_team_by_uuid(server.teams[1]->uuid, &server), 1);
    cr_assert_eq(find_team_by_uuid("fake uuid", &server), -1);
    cr_assert_eq(find_team_by_name(NULL, &server), -1);
    cr_assert_eq(find_team_by_name(server.teams[1]->team_name, NULL), -1);
    cr_assert_eq(find_team_by_name(server.teams[1]->team_name, &server), 1);
    cr_assert_eq(find_team_by_name("fake name", &server), -1);
    destroy_server(&server);
    server.teams = NULL;
    cr_assert_eq(find_team_by_name("nothing", &server), -1);
    cr_assert_eq(find_team_by_uuid("nothing", &server), -1);
}
