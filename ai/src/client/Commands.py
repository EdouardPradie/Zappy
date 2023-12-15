##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Commands
##

BUFFER_SIZE = 1024
from ai.src.broadcast.broadcast import set_broadcast_by_team


class Commands():
    def parse_inventory(self, response, inventory: dict) -> None:
        tab = response.removeprefix('[').removesuffix(']').strip().split(',')
        for item in tab:
            parts = item.strip().split(' ')
            if len(parts) >= 2:
                key = parts[0]
                value = int(parts[1])
                if key in inventory:
                    inventory[key] = value
            else:
                print("Invalid inventory item:", item)
        print("+++++++++++++++++++++++++")
        print(f"Inventory: {inventory}")

    def parse_look(self, response, look: dict):
        tab = response.removeprefix('[').removesuffix(']').split(',')
        for i,item in enumerate(tab):
            parts = item
            look[i] = parts
        print("+++++++++++++++++++++++++")
        print(f"Look: {look}")

    def nb_player_in_team(self, response, nb_player: int):
        nb_player = int(response)
        print("+++++++++++++++++++++++++")
        print(f"Player number: {nb_player}")

    def broadcast(self, team, broadcast_text) -> str:
        action_to_do = "Broadcast " + set_broadcast_by_team(int(team.split("m")[1]) ,broadcast_text)
        return action_to_do

    def take_object(self, object_to_take: str) -> str:
        action_to_do = "Take " + object_to_take
        return action_to_do

    def set_object(self, object_to_set) -> str:
        action_to_do = "Set " + object_to_set
        return action_to_do

    def eject(self):
        print("Eject")
        # action_to_do = "Eject " + team
        # return action_to_do