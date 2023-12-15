##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Client
##

from sys import exit
import socket
import selectors
from time import sleep
from socket import AF_INET, SOCK_STREAM
from ai.src.algorithm.Ai import Artifical_intelligence
from ai.src.broadcast.broadcast import get_broadcast_by_team

BUFFER_SIZE: int = 4096
EPITECH_SUCCESS: int = 0
EPITECH_ERROR: int = 84
MAX_CONSECUTIVE_REQUESTS: int = 10
UNICODE: str = "utf-8"


class Client():
    def __init__(self, hostname: str, port: str, team_name: str):
        self.name = team_name
        self.machine = hostname
        self.port = port
        self.socket = None
        if self.socket is None:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        else:
            self.socket = socket
        self.ai = Artifical_intelligence(self.name)
        self.selectors = selectors.DefaultSelector()
        self.client_num = 0
        self.connected_player = 0
        self.pending_player = 0
        self.init_condition = False
        self.looking_or_inventory = False
        self.last_message = ""

    def start_connection(self):
        try:
            server_address = (self.machine, self.port)
            self.socket.setblocking(False)
            self.socket.connect_ex(server_address)
            self.events = selectors.EVENT_READ | selectors.EVENT_WRITE
            self.selectors.register(self.socket, self.events)
        except socket.error as socketErr:
            print("Error while connecting to server: ", socketErr)
            exit(EPITECH_ERROR)
        except ValueError as e:
            print("Server connexion error:", e)

    def get_broadcast_in_my_team(self, cord: int, message: str):
        if message is None:
            return
        if int(message[-1]) != self.ai.level:
            return
        if "evolution" in message and int(message[-1]) == self.ai.level and self.ai.miam == True and self.ai.go_levelup == False:
            self.ai.turn_to_broadcast(cord)
            return

    def parse_response(self, response: str):
        if "WELCOME" in response:
            self.ai.action_to_do = (self.name + '\n')
            self.ai.actif = True
            return
        elif "dead" in response:
            print("Death of player number: ")
            self.close()
            exit(EPITECH_SUCCESS)
        elif "Current level:" in response:
            self.ai.actif = True
            self.ai.level = int(response.split(':')[1].strip().split('\n')[0])
            if self.ai.level == 8:
                print("VICTOIRE")
                self.close()
                exit(EPITECH_SUCCESS)
            return
        elif "Elevation underway" in response:
            self.ai.actif = False
            return
        elif response.isdigit() == True:
            self.ai.commands.nb_player_in_team(response, self.ai.nb_player)
            self.ai.actif = True
            return
        elif response.startswith("["):
            if (response[6].isdigit() == True or response[7].isdigit() == True):
                self.ai.commands.parse_inventory(response, self.ai.inventory)
                self.ai.value_up_to_date = True
            else:
                self.ai.commands.parse_look(response, self.ai.look)
            self.ai.actif = True
            return
        elif "message" in response:
            self.last_message = response
            self.get_broadcast_in_my_team(int(response.split(' ')[1][0]), get_broadcast_by_team(response.split(',')[1].strip()))
            return
        elif "ok" in response or "ko" in response:
            self.ai.actif = True
        elif self.init_condition == False:
            self.init_condition = True
            self.ai.actif = True
            return
        return

    def launcher(self):
        data_array = []
        tmp = ""
        recieve_data = ""
        try:
            while True:
                event = self.selectors.select(timeout=None)
                for _, mask in event:
                    if mask & selectors.EVENT_READ:
                        data_array = self.socket.recv(BUFFER_SIZE).decode(UNICODE).split("\n")
                        for recieve_data in data_array:
                            if recieve_data == "":
                                continue
                            # if recieve_data.strip() in self.last_message and self.last_message != "":
                            #     self.ai.algo()
                            #     continue
                            print("\nEVENT READ")
                            if recieve_data.startswith("["):
                                self.looking_or_inventory = True
                            if recieve_data.endswith("]"):
                                tmp += recieve_data
                                recieve_data = tmp
                                tmp = ""
                                self.looking_or_inventory = False
                            if self.looking_or_inventory == True:
                                tmp += recieve_data
                            else:
                                print(f"recieve_data: {recieve_data}")
                                self.parse_response(recieve_data.strip())

                    if mask & selectors.EVENT_WRITE:
                        if (self.init_condition == True and self.ai.actif == True):
                            self.ai.algo()
                        if (self.ai.action_to_do != "" and self.ai.actif == True):
                            print("\nEVENT_WRITE")
                            if self.name in self.ai.action_to_do:
                                self.init_condition = True
                            self.socket.sendall((self.ai.action_to_do + "\n").encode())
                            print(f"send data: {self.ai.action_to_do}")
                            if "Broadcast" in self.ai.action_to_do:
                                sleep(0.25)
                            if self.ai.nb_broadcast > 4:
                                self.ai.delay_broadcast += 1
                                print(f"delay broad: {self.ai.nb_broadcast}")
                            if self.ai.delay_broadcast >= 20:
                                self.ai.nb_broadcast = 0
                                self.ai.delay_broadcast = 0
                            self.ai.action_to_do = ""
                            self.ai.actif = False

        except ValueError as valueErr:
            print("Inappropriate argument value:", str(valueErr))
            self.socket.close()
        except KeyboardInterrupt as keybInterr:
            print("KeyboardInterrupt:", str(keybInterr))
            self.socket.close()

    def close(self):
        self.selectors.unregister(self.socket)
        self.socket.close()