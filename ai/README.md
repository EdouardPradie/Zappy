# Zappy - AI
Handling the Trantorian's world.

## Project
The final goal is to create a client, in free language (here python), that drives an player through orders sent to the server.

### Requirements
* The ai client is autonomous.
* After it’s launched the user has no more influence on how it functions.
* It drives a drone (the player).
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
| `make`           | Builds a `zappy_ai` executable.         |
| `make clean`     | Cleans build dumps, keeping the executable.     |
| `make fclean`    | Removes all of the files created by the build.  |
| `make re`        | Calls `make fclean` and then `make`.            |

### Launch project
```bash
> ./zappy_ai –help
USAGE: ./zappy_ai -p port -n name -h machine
port is the port number
name is the name of the team
machine is the name of the machine; localhost by default
```

|   Argument        |   Default value       |
| ----------------- | --------------------- |
|  -p `port`        | 4242                  |
|  -n `team names`  | `Team1`, `Team2`, `Team3`, `Team4`    |
