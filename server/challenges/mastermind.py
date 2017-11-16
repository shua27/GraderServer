from pprint import pprint

from server import app

# Default number of colors and pegs
__number_of_colors = 6
__number_of_pegs = 4


@app.route('/Mastermind/SetConfig/<number_of_colors>/number_of_pegs')
def set_configuration(number_of_colors, number_of_pegs):
    global __number_of_colors
    global __number_of_pegs

    __number_of_colors = number_of_colors
    __number_of_pegs = number_of_pegs

    return "OK"


@app.route('/Mastermind/CreateChallenge/', methods=['GET'])
def request_new_game():
    return {"Command": "ReportMastermindStarted",
            "Args": {"ColorList": range(1, __number_of_colors), "PegCount": __number_of_pegs}}


@app.route('/Mastermind/Guess/', methods=['POST'])
def request_mastermind_move(data):
    print("Mastermind move received. Data:")
    pprint(data)
