# Zappy - Server
Handling the Trantorian's world.

## Project
The goal of the server is to implement the world of [Trantor](https://github.com/Lukacms/Zappy/tree/main/docs/Trantor.md) in a C network server.
It must handle:
* the resources
* the game
* requests from the GUI client and the AI client (player)

### Requirements
* Must be executed with only one process and thread
* Use `select` to handle [socket multiplexing](https://dev.to/progrium/the-history-and-future-of-socket-level-multiplexing-1d5n)
* Communicate via [TCP sockets](https://www.ibm.com/docs/en/zvse/6.2?topic=SSB27H_6.2.0/fa2ti_what_is_socket_connection.htm)

## Client / Server communication
All commands are transmitted through a character string that ends with a new line.

### AI
The command may cause a delay for the next commands, defined in the `Time limit` column. It's `n` seconds divided by the `freq` given in parameter.

An AI is identified as one by typing a team name after recieving the connection message confirmation:
```
> WELCOME\n
< Team-name\n
> Client-num\n
> X Y\n
```

| Action            | Command           | Time limit        | Response                  |
| ----------------- | ----------------- | ----------------- | ------------------------- |
| Move up one tile  | Forward           |  7/f              | ok                        |
| Turn 90° right    | Right             |  7/f              | ok                        |
| Turn 90° left     | Left              |  7/f              | ok                        |
| Look around       | Look              |  7/f              | [tile1,tile2,...]         |
| Inventory         | Inventory         |  1/f              | [linemate n, sibur n, ...]|
| Broadcast text    | Broadcast [text]  |  7/f              | ok                        |
| Nb of team unused slots | Connect_nbr |  -                | value               |
| Fork a player     | Fork              |  42/f             | ok                        |
| Eject player of the same tile | Eject | 7/f               | ok/ko         |
| Death of a player | -                 | -                 | dead                      |
| Take object       | Take [object]     | 7/f               | ok/ko                     |
| Set object down   | Set [object]      | 7/f               | ok/ko                     |
| Start incantation | Incantation       | 300/f             | Elevation underway, Current level [n] / ko |

### GUI
The commands are mostly send by the clients when an action is done to give informations to the GUI for it to update its graphic rendering.

A GUI client is identified by typing `GRAPHIC` after recieving the connection message confirmation:
```
> WELCOME\n
< GRAPHIC\n
> msz
> sgt
> mct
> tna
> *connected clients*
```

|  Server *(message sent to client)*  |  Client *(message recieved)*  |  Details  |
| ----------- | ---------- | ------------ |
| msz X Y\n | msz\n | map size |
| bct X Y q0 q1 q2 q3 q4 q5 q6\n | bct X Y\n | content of a tile |
| bct X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles |  mct\n | content of the map (all the tiles) |
| tna N\n * nbr_teams | tna\n | name of all the teams |
| pnw #n X Y O L N\n | | connection of a new player |
| ppo n X Y O\n | ppo #n\n | player’s position |
| plv n L\n | plv #n\n | player’s level |)*
| pin n X Y q0 q1 q2 q3 q4 q5 q6\n | pin #n\n | player’s inventory |
| pex n\n | | expulsion |
| pbc n M\n | | broadcast |
| pic X Y L n n . . . \n | | start of an incantation (by the first player) |
| pie X Y R\n | | end of an incantation |
| pfk n\n | | egg laying by the player |
| pdr n i\n | |  resource dropping |
| pgt n i\n | | resource collecting |
| pdi n\n | | death of a player |
| enw e n X Y\n | | an egg was laid by a player |
| ebo e\n | | player connection for an egg |
| edi e\n | | death of an egg |
| sgt T\n | sgt\n | time unit request |
| sst T\n | sst T\n | time unit modification |
| seg N\n | | end of game |
| smg M\n | | message from the server |
| suc\n | | unknown command |
| sbp\n | | command parameter|

## How to build project ?
The project is build with a `Makefile`, with the following rules:

| Command          | Result                                          |
| ---------------- | ----------------------------------------------- |
| `make`           | Builds a `zappy_server` executable.         |
| `make clean`     | Cleans build dumps, keeping the executable.     |
| `make fclean`    | Removes all of the files created by the build.  |
| `make re`        | Calls `make fclean` and then `make`.            |
| `make tests_run` | Run tests made with [criterion](https://criterion.readthedocs.io/en/master/intro.html).               |

### Launch project
```bash
> $ ./zappy_server -h
USAGE	./zappy-server-p port -x width -y height -n name1 name2 ... -c clientsNb -f freq
	port	is the port number
	width	is the width of the world
	height	is the height of the world
	nameX	is the name of the team X
	clientsNb	is the number of authorized clients per team
	freq	is the reciprocal of time unit for execution of actions
```

|   Argument        |   Default value       |
| ----------------- | --------------------- |
|  -p `port`        | 4242                  |
|  -x `width`       | 10                    |
|  -y `height`      | 10                    |
|  -n `team names`  | `Team1`, `Team2`, `Team3`, `Team4`    |
|  -c `clientsNb`   | 3                     |
|  -f `freq`        | 100                   |
