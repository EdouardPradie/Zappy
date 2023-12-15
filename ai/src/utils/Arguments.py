##
## EPITECH PROJECT, 2023
## zappy
## File description:
## Arguments
##

from argparse import SUPPRESS, ArgumentParser

class Argument():
    def parse_arg():
        parser = ArgumentParser(description="zappy_ai", add_help=False)
        parser.add_argument("--help", action="help", help=SUPPRESS)
        parser.add_argument("-p", "--port", required=True, type=int, help="is the port number", dest="port")
        parser.add_argument("-n", "--name", required=True, type=str, help="is the name of the team", dest="name")
        parser.add_argument("-h", "--hostname", required=False, type=str, help="is the name of the machine; localhost by default", default="localhost", dest="machine")
        parsed_arg = parser.parse_args()
        return (parsed_arg.machine, parsed_arg.port, parsed_arg.name)
