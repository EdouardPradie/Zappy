##
## EPITECH PROJECT, 2023
## zappy
## File description:
## broadcast
##

import json

def get_broadcast_by_team(message: str) -> str:
    file = open('ai/asset/broadcast.json')
    data = json.load(file)
    for itea in range(4):
        for i in data['Broadcast'][itea]:
            if (data['Broadcast'][itea][i] == message):
                return i
    file.close()

def set_broadcast_by_team(team: int, message: str) -> str:
    file = open('ai/asset/broadcast.json')
    data = json.load(file)
    result = "AAAAAAAHHHHHHHH"
    print("team :", team)
    print("message :", message)
    for i in data['Broadcast'][team - 1]:
        if (message == i):
            result = data['Broadcast'][team - 1][message]
    file.close()
    return result
