##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Ai
##

import socket
import random
from ai.src.client.Commands import Commands

RESOURCES = ['food', 'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']
ELEVATION_RITUAL = {
    1: {'player' : 1, 'food' : 7, 'linemate' : 1},
    2: {'player' : 2, 'food' : 7, 'linemate' : 1, 'deraumere' : 1, 'sibur' : 1},
    3: {'player' : 2, 'food' : 7, 'linemate' : 2, 'sibur' : 1, 'phiras' : 2},
    4: {'player' : 4, 'food' : 7, 'linemate' : 1, 'deraumere' : 1, 'sibur' : 2, 'phiras' : 1},
    5: {'player' : 4, 'food' : 7, 'linemate' : 1, 'deraumere' : 2, 'sibur' : 1, 'mendiane' : 3},
    6: {'player' : 6, 'food' : 7, 'linemate' : 1, 'deraumere' : 2, 'sibur' : 3, 'phiras' : 1},
    7: {'player' : 6, 'food' : 7, 'linemate' : 2, 'deraumere' : 2, 'sibur' : 2, 'mendiane' : 2, 'phiras' : 2, 'thystame' : 1},
    }
ITEM_VALUE = {'player' : -5, 'food' : 3, 'linemate' : 1, 'deraumere' : 2, 'sibur' : 3, 'mendiane' : 4, 'phiras' : 5, 'thystame' : 6}
BUFFER_SIZE = 4096

class Artifical_intelligence():
    def __init__(self, team_name: str):
        self.actif = False
        self.first_action = True
        self.value_up_to_date = False
        self.miam = False
        self.look = {}
        self.inventory = {'food' : 0, 'linemate' : 0, 'deraumere' : 0, 'sibur' : 0, 'mendiane' : 0, 'phiras' : 0, 'thystame' : 0}
        self.nb_player = 1
        self.broadcast_text = ""
        self.team_name = team_name
        self.level = 1
        self.previous_action = ""
        self.action_to_do = ""
        self.prog_action = []
        self.commands = Commands()
        self.nb_broadcast = 0
        self.delay_broadcast = 0
        self.nb_player_ready_to_incantation = 0

    def object_needed(self, value) -> bool:
        print("OBJECT NEEDED")
        if self.look[value].count("player") > 2:
            return False
        for item in ELEVATION_RITUAL[self.level].keys():
            if "player" not in item and \
                item in self.look[value] and \
                self.inventory[item] < ELEVATION_RITUAL[self.level][item]:
                return True
        return False

    def get_object(self, value) -> bool:
        print(">>>>>>>>>>>>>>>>>>>>GET OBJECT")
        for item in self.look[value].split(' '):
            if (item != 'player' and item != ''):
                self.prog_action.append(self.commands.take_object(item))
        return True

    def turn_to_broadcast(self, direction: int):
        print(">>>>>>>>>>>>>>>>>>>>TURN TO BROADCAST")
        self.prog_action = []
        self.look = {}
        self.go_levelup = True
        self.value_up_to_date = False
        if (direction == 0):
            self.actif = False
            return
        if (direction == 1):
            self.prog_action.append("Forward\n")
            return
        if (direction == 2):
            self.prog_action.append("Forward\n")
            self.prog_action.append("Left\n")
            self.prog_action.append("Forward\n")
            return
        if (direction == 3):
            self.prog_action.append("Left\n")
            self.prog_action.append("Forward\n")
            return
        if (direction == 4):
            self.prog_action.append("Left\n")
            self.prog_action.append("Forward\n")
            self.prog_action.append("Left\n")
            self.prog_action.append("Forward\n")
            return
        if (direction == 5):
            self.prog_action.append("Left\n")
            self.prog_action.append("Left\n")
            self.prog_action.append("Forward\n")
            return
        if (direction == 6):
            self.prog_action.append("Right\n")
            self.prog_action.append("Forward\n")
            self.prog_action.append("Right\n")
            self.prog_action.append("Forward\n")
            return
        if (direction == 7):
            self.prog_action.append("Right\n")
            self.prog_action.append("Forward\n")
            return
        if (direction == 8):
            self.prog_action.append("Forward\n")
            self.prog_action.append("Right\n")
            self.prog_action.append("Forward\n")
            return

    def check_if_evolution(self) -> bool:
        print(">>>>>>>>>>>>>>>>>>>>CHECK IF EVOLUTION")
        if self.miam == False:
            return False
        for item in ELEVATION_RITUAL[self.level].keys():
            if "player" in item:
                continue
        if len(self.look) <= 1:
            return False
        if self.look[0].count("player") < ELEVATION_RITUAL[self.level]["player"]:
            self.nb_broadcast += 1
            print(f"nb broad: {self.nb_broadcast}")
        if self.look[0].count("player") < ELEVATION_RITUAL[self.level]["player"] and self.level < 4:
            if (self.delay_broadcast == 0):
                self.prog_action.append(self.commands.broadcast(self.team_name ,"evolution" + str(self.level)))
            return True
        if self.look[0].count("player") < ELEVATION_RITUAL[self.level]["player"] and self.level > 3 and random.randint(1, 10) >= (self.level + 3) and self.delay_broadcast == 0:
            self.prog_action.append(self.commands.broadcast(self.team_name ,"evolution" + str(self.level)))
            return True
        for item in ELEVATION_RITUAL[self.level].keys():
            if "food" not in item and "player" not in item and self.inventory[item] >= ELEVATION_RITUAL[self.level][item]:
                for _ in range(ELEVATION_RITUAL[self.level][item]):
                    self.prog_action.append(self.commands.set_object(item))
        self.prog_action.append("Incantation")
        return True

    def go_track_obj(self, tile, x, y) -> bool:
        print(">>>>>>>>>>>>>>>>>>>>GO TRACK OBJ")
        for _ in range(y):
            self.prog_action.append("Forward\n")
        if (x < 0):
            self.prog_action.append("Left\n")
            x = x * -1
            for _ in range(x):
                self.prog_action.append("Forward\n")
            return self.get_object(tile)
        if (x > 0):
            print("RIGHT")
            self.prog_action.append("Right\n")
            for _ in range(x):
                self.prog_action.append("Forward\n")
        return self.get_object(tile)

    def track_obj_set(self) -> bool:
        print(">>>>>>>>>>>>>>>>>>>>TRACK OBJ SET")
        y = 0
        x = 0
        max_y = 0
        max_x = 0
        max_tile = 0
        value = 0
        value_tmp = 0
        for tile in range(len(self.look)):
            if (self.object_needed(tile) == True):
                return self.go_track_obj(tile, x, y)
            value_tmp = 0
            for item in self.look[tile].split(' '):
                if item in ITEM_VALUE:
                    value_tmp += ITEM_VALUE.get(item, 0)
            if value_tmp > value:
                value = value_tmp
                max_y = y
                max_x = x
                max_tile = tile
            if (y == x):
                y += 1
                x = y * -1
            else:
                x += 1
        if max_tile == 0:
            return False
        return self.go_track_obj(max_tile, max_x, max_y)

    def check_if_food(self, tile) -> bool:
        print(">>>>>>>>>>>>>>>>>>>>CHECK IF FOOD")
        if "food" in self.look[tile]:
            return True
        return False

    def go_track_food(self, tile, x, y) -> bool:
        print(">>>>>>>>>>>>>>>>>>>>GO TRACK FOOD")
        for _ in range(y):
            self.prog_action.append("Forward\n")
        if (x < 0):
            self.prog_action.append("Left\n")
            x = x * -1
            for _ in range(x):
                self.prog_action.append("Forward\n")
            return self.get_object(tile)
        if (x > 0):
            self.prog_action.append("Right\n")
            for _ in range(x):
                self.prog_action.append("Forward\n")
        return self.get_object(tile)

    def track_food(self) -> bool:
        print(">>>>>>>>>>>>>>>>>>>>TRACK FOOD")
        y = 0
        x = 0
        for tile in range(len(self.look)):
            if (self.check_if_food(tile) == True):
                self.go_track_food(x, y)
                return True
            if (y == x):
                y += 1
                x = y * -1
            else:
                x += 1
        self.prog_action.append("Right\n")
        return False

    def track_player(self) -> bool:
        print(">>>>>>>>>>>>>>>>>>>>TRACK PLAYER")
        y = 0
        x = 0
        for tile in range(1, len(self.look)):
            if (self.check_if_alone(tile) == True):
                self.go_track_player(x, y)
                return True
            if (y == x):
                y += 1
                x = y * -1
            else:
                x += 1
        return False

    def check_if_alone(self, tile) -> bool:
        print(">>>>>>>>>>>>>>>>>>>>CHECK IF ALONE")
        if "player" in self.look[tile]:
            return True
        return False

    def go_track_player(self, x, y) -> None:
        print(">>>>>>>>>>>>>>>>>>>>GO TRACK PLAYER")
        for _ in range(y):
            print("Forward")
            self.prog_action.append("Forward\n")
        if (x < 0):
            print("LEFT")
            self.prog_action.append("Left\n")
            x = x * -1
            for _ in range(x):
                print("Forward")
                self.prog_action.append("Forward\n")
            return
        if (x > 0):
            print("RIGHT")
            self.prog_action.append("Right\n")
            for _ in range(x):
                print("Forward")
                self.prog_action.append("Forward\n")
        return

    def requirements_analysis(self) -> None:
        print(">>>>>>>>>>>>>>>>>>>>REQUIREMENTS ANALYSIS")
        if (random.randint(1, 10) >= 10 and self.level == 1):
            self.prog_action.append("Fork")
            self.fork = 1
            return
        if self.track_obj_set() == False:
            self.prog_action.append("Right")

    def check_if_incantation(self) -> bool:
        print(">>>>>>>>>>>>>>>>>>>>CHECK IF INCANTATION")
        nb_player = self.look[0].count("player")
        nb_linemate = self.look[0].count("linemate")
        nb_sibur = self.look[0].count("sibur")
        if nb_player >= 2 and nb_linemate >= 2 and nb_sibur >= 2:
            self.decision_to_steal_object()
            return True
        return False

    def decision_to_steal_object(self) -> bool:
        if self.object_needed(socket) == True:
            return True
        else:
            self.prog_action.append("Eject")
            return False

    def algo(self):
        self.is_processing = True
        print(f"========================= lvl:{self.level}")
        if (self.prog_action == []):
            self.go_levelup = False
            if self.value_up_to_date == True:
                if (self.inventory["food"] < 8):
                    self.miam = False
                if (self.inventory["food"] > 11):
                    self.miam = True
                if self.miam == False:
                    self.requirements_analysis()
                if (self.check_if_evolution() == False):
                    self.requirements_analysis()
                elif (self.track_player() == False):
                    self.prog_action.append("Forward")
                self.value_up_to_date = False
            else:
                self.prog_action.append("Look")
                self.prog_action.append("Inventory")
        if (self.prog_action != []):
            self.action_to_do = self.prog_action[0]
            self.prog_action = self.prog_action[1:]
            self.previous_action = self.action_to_do
            print("action to do: ", self.action_to_do)
        # print(f"========================= lvl:{self.level}")
        # if self.first_action == True:
        #     self.prog_action.append("Look")
        #     self.prog_action.append("Inventory")
        # elif (self.prog_action == []):
        #     if (self.inventory["food"] > 8):
        #         print("Enough food")
        #     else:
        #         self.track_food()
        # else:
        #     self.action_to_do = self.prog_action[0]
        #     self.prog_action = self.prog_action[1:]
        #     self.previous_action = self.action_to_do
        #     print("action to do: ", self.action_to_do)
        # self.first_action = False