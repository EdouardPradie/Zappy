/*
** EPITECH PROJECT, 2023
** src
** File description:
** main
*/

#include <stdlib.h>
#include <zappy/config/arguments.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

static args_config_t default_config(void)
{
    args_config_t args = {0};

    args.freq = DEFAULT_FREQ;
    args.nb_clients_og = DEFAULT_CLIENTS;
    args.world = (vector2i_t){DEFAULT_WIDTH, DEFAULT_HEIGHT};
    return args;
}

int main(int argc, char *const argv[])
{
    args_config_t args = default_config();

    srand(time(NULL));
    if (parse_args(&args, argc, argv) != SUCCESS) {
        if (args.team_names)
            free_array(args.team_names);
        return print_help(FAILURE);
    }
    if (args.help)
        return print_help(SUCCESS);
    return launch(&args);
}
