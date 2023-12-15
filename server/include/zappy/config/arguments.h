/*
** EPITECH PROJECT, 2023
** parse
** File description:
** arguments
*/

#pragma once

#include <stddef.h>

/* default arguments */
#define DEFAULT_PORT 4242
#define DEFAULT_FREQ 100
#define DEFAULT_HEIGHT 10
#define DEFAULT_WIDTH 10
#define DEFAULT_CLIENTS 3
static __attribute__((unused))
const char *DEFAULT_TEAMS[] = {"Team1", "Team2", "Team3", "Team4", NULL};

/* OPTARGS */
#define SHORT_ARGS "p:x:y:n:c:hf:"

/* errors */
#define ERROR_PORT "Invalid port number. Must be a strictly positive int.\n"
#define ERROR_WIDTH "Invalid width. Must be a strictly positive int.\n"
#define ERROR_HEIGHT "Invalid height. Must be a strictly positive int.\n"
#define ERROR_CLIENTS \
    "Invalid number of clients. Must be a strictly positive int.\n"
#define ERROR_FREQ "Invalid frequency. Must be a strictly positive int.\n"
#define ERROR_TEAM_NAME "Team names must be unique.\n"

typedef struct vector2i_s {
    size_t x;
    size_t y;
} vector2i_t;

/* store arguments information */
/*
    @param port - int
    @param nb clients og - int
    @param world - vector2i
    @param freq - int
    @param team names - char **
*/
typedef struct args_config_s {
    int port;
    vector2i_t world;
    int nb_clients_og;
    int freq;
    char **team_names;
    int help;
} args_config_t;

typedef int (*flag_handler_t)(args_config_t *, char *const[], int);

typedef struct flag_handler_binder_s {
    int cases;
    flag_handler_t handler;
} flag_handler_binder_t;

/* functions */
int parse_args(args_config_t *, int, char *const[]);

/* functions pointers */
int c_handler(args_config_t *, char *const[], int);
int f_handler(args_config_t *, char *const[], int);
int h_handler(args_config_t *, char *const[], int);
int n_handler(args_config_t *, char *const[], int);
int p_handler(args_config_t *, char *const[], int);
int x_handler(args_config_t *, char *const[], int);
int y_handler(args_config_t *, char *const[], int);
