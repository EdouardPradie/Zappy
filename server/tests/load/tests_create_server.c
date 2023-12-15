/*
** EPITECH PROJECT, 2023
** tests
** File description:
** launch
*/

#include <criterion/criterion.h>
#include <criterion/internal/redirect.h>
#include <zappy/config/config.h>
#include <zappy/server.h>
#include <zappy/server/destroy.h>

void redirect(void);

static char **dup_array(const char *const origin[])
{
    char **dest = NULL;
    int i = 0;

    if (!origin)
        return NULL;
    while (origin[i])
        i++;
    if (!(dest = malloc(sizeof(char *) * (i + 1))))
        return NULL;
    for (int y = 0; y < i; y++) {
        if (!(dest[y] = strdup(origin[y])))
            return NULL;
    }
    dest[i] = NULL;
    return dest;
}

Test(create_server, null_arguments)
{
    cr_assert_eq(create_server(NULL, NULL), FAILURE);
}

Test(create_server, null_args)
{
    server_t server = {0};

    cr_assert_eq(create_server(&server, NULL), FAILURE);
}

Test(update_server_with_args, basic_server)
{
    args_config_t args = {
        .freq = DEFAULT_FREQ,
        .help = false,
        .nb_clients_og = DEFAULT_CLIENTS,
        .port = DEFAULT_PORT,
        .world = (vector2i_t){.x = DEFAULT_WIDTH, .y = DEFAULT_HEIGHT},
        .team_names = dup_array(DEFAULT_TEAMS),
    };
    server_t server = {0};

    cr_assert_eq(update_server_with_args(&server, &args), SUCCESS);
    destroy_arguments(&args);
    destroy_server(&server);
}
