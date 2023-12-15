/*
** EPITECH PROJECT, 2023
** options
** File description:
** n_handler
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <zappy/config/arguments.h>
#include <zappy/server.h>
#include <zappy/server/utils.h>

static int check_doubles(char *team_names[], char to_cmp[])
{
    for (unsigned int i = 1; team_names[i]; i++)
        if (strcmp(team_names[i], to_cmp) == SUCCESS)
            return FAILURE;
    return SUCCESS;
}

int n_handler(args_config_t *args, char *const argv[], int argc)
{
    int size = 0;

    --optind;
    while (optind < argc && argv[optind] && argv[optind][0] != '-') {
        size++;
        args->team_names =
            realloc_array(args->team_names, size, strlen(argv[optind]));
        if (!args->team_names)
            return FAILURE;
        args->team_names[size - 1] =
            strcpy(args->team_names[size - 1], argv[optind]);
        optind++;
    }
    for (unsigned int i = 0; args->team_names[i]; i++)
        if (check_doubles(args->team_names + i, args->team_names[i]) != SUCCESS)
            return set_error(STDERR_FILENO, ERROR_TEAM_NAME, false);
    return SUCCESS;
}
