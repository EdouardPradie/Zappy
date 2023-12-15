/*
** EPITECH PROJECT, 2023
** server
** File description:
** summons
*/

#pragma once

#define NOT_FOUND -1
#define MAX_WAITING_SUMMONS 10
#define BUFFER_SIZE 4096
#define SEPARATOR_CMD " \t\r\n"

#define CLIENT_CONNECT "WELCOME\n"

#define INVALID_ACTION "ko\n"
#define UNKNOWN_COMMAND "ko\n"

#define GUI_INDIC "GRAPHIC\n"
#define GUI_UNKNOWN "suc\n"

#define GO_LEVEL_2 "1100000"
#define GO_LEVEL_3 "2111000"
#define GO_LEVEL_4 "2201020"
#define GO_LEVEL_5 "4112010"
#define GO_LEVEL_6 "4121300"
#define GO_LEVEL_7 "6123010"
#define GO_LEVEL_8 "6222221"

/* summons of GUIs */
#define ZAPPY_GUI_CONNECT "GRAPHIC"
#define ZAPPY_MSG "msz"
#define ZAPPY_BCT "bct"
#define ZAPPY_TNA "mct"
#define ZAPPY_PNW "tna"
#define ZAPPY_PPO "ppo"
#define ZAPPY_PLV "plv"
#define ZAPPY_PIN "pin"
#define ZAPPY_SGT "sgt"
#define ZAPPY_SST "sst"

/* summons of AIs */
#define ZAPPY_FORWARD "Forward"
#define ZAPPY_RIGHT "Right"
#define ZAPPY_LEFT "Left"
#define ZAPPY_LOOK "Look"
#define ZAPPY_INVENTORY "Inventory"
#define ZAPPY_BROADCAST "Broadcast"
#define ZAPPY_CONNECT_NBR "Connect_nbr"
#define ZAPPY_FORK "Fork"
#define ZAPPY_EJECT "Eject"
#define ZAPPY_TAKE "Take"
#define ZAPPY_SET "Set"
#define ZAPPY_INCANTATION "Incantation"

/* delay for summons of AIs */
#define RESTRAINT_FORWARD 7
#define RESTRAINT_RIGHT 7
#define RESTRAINT_LEFT 7
#define RESTRAINT_LOOK 7
#define RESTRAINT_INVENTORY 1
#define RESTRAINT_BROADCAST 7
#define RESTRAINT_FORK 42
#define RESTRAINT_EJECT 7
#define RESTRAINT_TAKE 7
#define RESTRAINT_SET 7
#define RESTRAINT_INCANTATION 300

/* command to send to GUIs */
#define DISPATCH_MSZ "msz %zu %zu\n" // map size
#define DISPATCH_BCT \
    "bct %zu %zu %zd %zd %zd %zd %zd %zd %zd\n"   // content of a tile
#define DISPATCH_TNA "tna %s\n"                   // name of all a team
#define DISPATCH_PNW "pnw %d %zu %zu %d %zu %s\n" // connection of a new player
#define DISPATCH_PPO "ppo %d %zu %zu %d\n"        // player’s position
#define DISPATCH_PLV "plv %d %zu\n"               // player’s level
#define DISPATCH_PIN\
    "pin %d %zu %zu %zd %zd %zd %zd %zd %zd %zd\n" // player's inventory
#define DISPATCH_PEX "pex %d\n"                    // expulsion
#define DISPATCH_PBC "pbc %d %s\n"                 // broadcast
#define DISPATCH_PIC "pic %zu %zu %zu %d"          // start of an incantation
#define DISPATCH_PIE "pie %zu %zu %d\n"            // end of an incantation
#define DISPATCH_PFK "pfk %d\n"                    // egg laying by the player
#define DISPATCH_PDR "pdr %d %d\n"                 // resource dropping
#define DISPATCH_PGT "pgt %d %d\n"                 // resource collecting
#define DISPATCH_PDI "pdi %d\n"                    // death of a player
#define DISPATCH_ENW "enw %d %d %zu %zu\n" // an egg was laid by a player
#define DISPATCH_EBO "ebo %d\n"            // player connection for an egg
#define DISPATCH_EDI "edi %d\n"            // death of an egg
#define DISPATCH_SGT "sgt %d\n"            // time unit request
#define DISPATCH_SST "sst %d\n"            // time unit modification
#define DISPATCH_SEG "seg %s\n"            // end of game
#define DISPATCH_SMG "smg %s\n"            // message from the server
#define DISPATCH_SUC "suc\n"               // unknown command
#define DISPATCH_SBP "sbp\n"               // command parameter

/* send commands to AI */
#define AI_EJECT "eject: %i\n"
#define AI_INVENTORY \
    "[food %li, linemate %li, deraumere %li, sibur %li, " \
    "mendiane %li, phiras " \
    "%li, thystame %li]\n"
#define BASIC_VALID "ok\n"
#define AI_DEATH "dead\n"
#define VALID_INCANT "Current level: %zu\n"
#define IN_INCANT "Elevation underway\n"

static const __attribute__((unused)) char *INCANTATION_MANDATORY[] = {
    "1100000", "2111000", "2201020", "4112010", "4121300", "6123010", "6222221",
};

typedef struct summon_queue_s {
    char *summon;
    int size;
} summon_queue_t;
