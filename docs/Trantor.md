# Zappy - A Trantorian world
The game is happening on a World, **Trantor**, and consists of managing it, and its inhabitants.

## The world
Trantor's history manual

### Geography
* Made up of zero-relief planes; there are no such things as: mountains, valleys, craters, ...
* What we see in the GUI, the game board represent the entirety of it
* This world is circular: if a player exit by one side of the world, they will return to the other

### Resources
It's a very rich world, and has a lot of resources, as well as food. If we were to rank theses by rarity (from most common to rarest), we would obtain this list:
|  Item     | Density       |
| --------- | ------------- |
| Food      | 0.5           |
| Linemate  | 0.3           |
| Deraumere | 0.15          |
| Sibur     | 0.1           |
| Mendiane  | 0.1           |
| Phiras    | 0.08          |
| Thystame  | 0.05          |

The resources are evenly spread accross the map, and respawn every `20` ticks.

## Trantorians

They are pacifists, and only need food to survive; one unit of it allow them to live `126` ticks longer. Their ultimate goal is to rise up their [world hierarchy](#Elevation).
They are dispatched by teams, but don't limit the interactions with only memebers of their team.
They are bodiless and don't bump into other [if they don't want to](#Actions).

Then, their main activities are:
* to feed themselves
* collecting stones that are needed to evolve

## Elevation
The Trantorians spawn at level 1, and they want to reach the peak of Trantorian society, with is the eighth level. To achieve this goal, they practice a ritual, which need, in addition to mental capacities
(taking `300` ticks from start to finish), a number of players and stones of each type. The players don't need to be on the same team, but on the same level and on the same tile (as well as the resources).
The ritual starts as soon as one of the players initiate the incantation.

The secret of the incantation, passed down from generation to generation come down the following requirements:
| Elevation     | Players       | Linemate      | Deraumere     | Sibur     | Mendiane      | Phiras    | Thystame      |
| ------------- | ------------- | ------------- | ------------- | --------- | ------------- | --------- | ------------- |
| 1->2          | 1             | 1             | 0             | 0         | 0             | 0         | 0             |
| 2->3          | 2             | 1             | 1             | 1         | 0             | 0         | 0             |
| 3->4          | 2             | 2             | 0             | 1         | 0             | 2         | 0             |
| 4->5          | 4             | 1             | 1             | 2         | 0             | 1         | 0             |
| 5->6          | 4             | 1             | 2             | 1         | 3             | 0         | 0             |
| 6->7          | 6             | 1             | 2             | 3         | 0             | 1         | 0             |
| 7->8          | 6             | 2             | 2             | 2         | 2             | 2         | 1             |

Thoses must be verified at the beginning **and** at the end of the ritual, and must be completed each time to achieve the elevation.

During this ritual, the Trantorian's mind and body are occupied, so they can't do anything else.

## Actions
What the Trantorians can do is limited to a few actions, wich are:
* Moving up one tile
* Turn 90° right
* Turn 90° left
* Look around
* [Look into their inventory](#Inventory)
* *Broadcast text* => Tell **every** Trantorians something
* Find the number of unused slots in their teams => *the solts belonging to an egg waiting for a player to connect*
* [Fork a player](#Reproduction) => make an egg, which will be a Trantorian once someone connect to it
* Eject players from the tile they're in => also destroy all eggs on the tile
* *Die* => from lack of food
* Take an object / set it down
* Start the incantation ritual

If they try to do any other thing, the server will answer `ko`.

### Time
The Trantorians have adopted an international time unit: seconds. All of the Trantorians actions take some time, which can be calculated from the formula:
$$
\frac{action}{f}
$$

### Reproduction

The players can reproduce with the command `Fork`, which produce a new egg. This add a slot to the player's team.

When a player connect to a team, an egg is randomly selected from the team on its position, and with a random orientation.

### Inventory
Allow the Trantorian to see what they have in their pouch. The output given back to them look like this:
`[food 345, sibur 3, phiras 5, ..., deraumere 0]\n`
