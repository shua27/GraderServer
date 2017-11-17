import json
import random

from flask import jsonify, request

from server import app

cache = {
    "number_of_colors": 6,
    "number_of_pegs": 4,
    "current_code": [],
    "guess_count": 0,
    "max_guesses": 300,
}


def _check_guess(guess):
    """

    :param guess: The client's guess at the current code.
    :return: A boolean indicating if the guess was correct.
    :return: An int representing the number of pegs in the correct positions
    :return: An int representing the number of correct colors in the wrong position
    """
    correct = True if guess == cache["current_code"] else False
    correct_pegs = 0
    correct_peg_colors = 0

    for idx, (a, b) in enumerate(zip(guess, cache["current_code"])):
        if a == b:
            correct_pegs += 1
            guess[idx] = -1

    for elem in cache["current_code"]:
        if elem in guess:
            correct_peg_colors += 1
            guess.remove(elem)

    return correct, correct_pegs, correct_peg_colors


if __name__ == "__main__":
    from pprint import pprint

    pprint(_check_guess([1, 2, 3, 4]))


@app.route('/')
def index():
    return "Index reached"


@app.route('/Mastermind/SetConfig/<number_of_colors>/number_of_pegs')
def set_configuration(number_of_colors, number_of_pegs):
    cache["number_of_colors"] = number_of_colors
    cache["number_of_pegs"] = number_of_pegs

    return "OK"


@app.route('/Mastermind/CreateChallenge', methods=['GET'])
def request_new_game():
    cache["current_code"] = [random.choice(list(range(1, cache["number_of_colors"])))
                             for _ in range(cache["number_of_pegs"])]

    print("Current code ={}".format(cache["current_code"]))

    return jsonify({"Command": "ReportMastermindStarted",
                    "Args": {"ColorList": list(range(1, cache["number_of_colors"])),
                             "PegCount": cache["number_of_pegs"]}})


@app.route('/Mastermind/Guess', methods=['POST'])
def request_mastermind_move():
    print("Mastermind move received. Data:")
    correct, correct_pegs, correct_peg_colors = _check_guess(request.get_json()["Args"]["BoardRow"])
    cache["guess_count"] += 1

    if cache["guess_count"] == cache["max_guesses"]:
        cache["guess_count"] = 0
        return jsonify({"Command": "ReportGameOver",
                        "Args": {"Correct": correct,
                                 "GuessCount": cache["guess_count"]}})
    else:
        return jsonify({"Command": "MastermindGuessResponse",
                        "Args": {"Correct": correct,
                                 "CorrectPegs": correct_pegs,
                                 "CorrectPegColors": correct_peg_colors}})
