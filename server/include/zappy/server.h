/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** server
*/

#pragma once

#include <zappy/server/infos.h>

#define SUCCESS 0
#define FAILURE 84

#define HELP \
    "USAGE\t./zappy-server-p port -x width -y height -n name1 name2 ... -c " \
    "clientsNb -f freq\n" \
    "\tport\tis the port number\n" \
    "\twidth\tis the width of the world\n" \
    "\theight\tis the height of the world\n" \
    "\tnameX\tis the name of the team X\n" \
    "\tclientsNb\tis the number of authorized clients per team\n" \
    "\tfreq\tis the reciprocal of time unit for execution of actions\n"
#define LONG_HELP "--help"
#define SHORT_HELP "-h"
#define PERROR_MSG "Zappy"

int launch(args_config_t *);
void handle_sigint(int);
void set_server(server_t *);
server_t *get_server(void);
int server_loop(server_t *);
int check_game_status(server_t *);
