/*
** EPITECH PROJECT, 2023
** clock
** File description:
** update_ticks
*/

#include <zappy/server/client.h>
#include <zappy/server/clock/utils.h>
#include <zappy/server/map_utils.h>
#include <zappy/server/summon/utils.h>

static void update_ai(server_t *server, int ticks_elapsed,
                        client_node_t *client)
{
    if (client->stats.action.type == ACTION &&
        ticks_elapsed >= client->stats.action.ticks) {
        client->stats.action.type = NOTHING;
        client->stats.action.ticks = -1;
    }
    if (client->stats.action.type == INCANTATION)
        check_incantation_end(server, client, ticks_elapsed);
    if (client->stats.action.type == NOTHING)
        handle_client_summon(pop_summon(client), client, server);
}

static void update_ticks_clients(server_t *server, int ticks_elapsed)
{
    client_node_t *client = 0;

    if (!(client = server->clients.head))
        return;
    for (unsigned int i = 0; i < server->clients.length; i++) {
        if (client->state == AI)
            update_ai(server, ticks_elapsed, client);
        else {
            handle_client_summon(pop_summon(client), client, server);
        }
        client = client->next;
    }
}

static void update_map_ticks(server_t *server, int ticks_elapsed)
{
    if (ticks_elapsed >= server->map.last_updated) {
        server->map.last_updated = ticks_elapsed + UPDATE_TICKS;
        update_map(server);
    }
}

void update_ticks(server_t *server)
{
    int ticks_elapsed = -1;

    if (!server || (ticks_elapsed = gettickselapsed(&server->clock)) <= 0)
        return;
    update_ticks_clients(server, ticks_elapsed);
    update_map_ticks(server, ticks_elapsed);
    if (ticks_elapsed >= server->clients.last_meal) {
        server->clients.last_meal = ticks_elapsed + MEAL_TIME;
        starve_players(server);
    }
}
