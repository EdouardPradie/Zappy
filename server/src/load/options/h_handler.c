/*
** EPITECH PROJECT, 2023
** options
** File description:
** h_handler
*/

#include <stdbool.h>
#include <zappy/config/arguments.h>
#include <zappy/server.h>

int h_handler(args_config_t *args, char __attribute__((unused)) *const argv[],
            int __attribute__((unused)) argc)
{
    args->help = true;
    return SUCCESS;
}
