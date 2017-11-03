from pprint import pprint


def request_new_game():
    return {"Command": "RequestNewGameResponse", "Args": {"Name": "Mastermind"}}


def request_mastermind_move(data):
    print("Mastermind move received. Data:")
    pprint(data)
