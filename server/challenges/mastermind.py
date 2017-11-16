from pprint import pprint
from random import randint


def _get_color_list():
    return ["GREEN", "BLUE", "RED"]


def _get_number_of_pegs():
    return randint(1, 5)


def request_new_game():
    return {"Command": "ReportMastermindStarted",
            "Args": {"ColorList": ["GREEN", "BLUE", "RED"], "PegCount": _get_number_of_pegs()}}


def request_mastermind_move(data):
    print("Mastermind move received. Data:")
    pprint(data)
