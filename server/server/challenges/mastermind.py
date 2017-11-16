import json
import random

from flask import jsonify, request

from server import app

# Default number of colors and pegs
__number_of_colors = 6
__number_of_pegs = 4

__current_code = []


@app.route('/')
def index():
    return "Index reached"


@app.route('/Mastermind/SetConfig/<number_of_colors>/number_of_pegs')
def set_configuration(number_of_colors, number_of_pegs):
    global __number_of_colors
    global __number_of_pegs

    __number_of_colors = number_of_colors
    __number_of_pegs = number_of_pegs

    return "OK"


@app.route('/Mastermind/CreateChallenge', methods=['GET'])
def request_new_game():
    global __current_code
    __current_code = [random.choice(list(range(1, __number_of_colors))) for _ in range(__number_of_pegs)]

    print("Current code ={}".format(__current_code))

    return jsonify({"Command": "ReportMastermindStarted",
                    "Args": {"ColorList": list(range(1, __number_of_colors)), "PegCount": __number_of_pegs}})


@app.route('/Mastermind/Guess', methods=['POST'])
def request_mastermind_move():
    print("Mastermind move received. Data:")
    # guess = json.loads(request.get_json())

    return jsonify({"Command": "MastermindGuessResponse",
                    "Args": {"Correct": False, "CorrectPegs": 0, "CorrectPegColors": 0}})
