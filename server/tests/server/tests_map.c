/*
** EPITECH PROJECT, 2023
** server
** File description:
** tests_map
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <zappy/server.h>
#include <zappy/server/client.h>
#include <zappy/server/destroy.h>
#include <zappy/server/map_utils.h>
#include <zappy/server/utils.h>

void redirect(void);
int create_default_server(server_t *server, int port);

Test(generate_map, generate_map)
{
    cr_assert_eq(generate_map(NULL), FAILURE);
}

Test(update_map, update_map)
{
    server_t server = {0};

    cr_assert_eq(update_map(NULL), FAILURE);
    cr_assert_eq(create_default_server(&server, 4245), SUCCESS);
    for (u_int y = 0; y < server.map.size.y; y++) {
        for (u_int x = 0; x < server.map.size.x; x++)
            if (server.map.tiles[y][x].slots[0].units > 0) {
                server.map.tiles[y][x].slots[0].units = 0;
                break;
            }
    }
    cr_assert_eq(update_map(&server), SUCCESS);
    // destroy_server(&server); // WARN segfault here for unknown reason
}

Test(change_player_pos, change_player_pos)
{
    server_t server = {0};
    vector2i_t invalid = {8666665, 27856};
    vector2i_t new_pos = {1, 0};
    client_node_t *client = malloc(sizeof(client_node_t));

    cr_assert_eq(create_default_server(&server, 4246), SUCCESS);
    client->uuid = generate_uuid();
    client->cfd = open("./tmp", O_CREAT | O_TRUNC | O_RDWR);
    cr_assert_eq(
        add_client_to_team(client, &server, server.teams[0]->team_name),
        SUCCESS);
    cr_assert_eq(change_player_pos(NULL, NULL, invalid, invalid), FAILURE);
    cr_assert_eq(change_player_pos(&server, NULL, invalid, invalid), FAILURE);
    cr_assert_eq(change_player_pos(&server, client->uuid, invalid, invalid),
                 FAILURE);
    cr_assert_eq(
        change_player_pos(&server, client->uuid, client->stats.pos, invalid),
        FAILURE);
    cr_assert_eq(
        change_player_pos(&server, client->uuid, client->stats.pos, new_pos),
        SUCCESS);
    remove("./tmp");
    destroy_server(&server);
}
