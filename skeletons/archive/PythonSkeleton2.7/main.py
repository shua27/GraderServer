import sys

from GameClasses import Game
import pprint

"""
This file is your skeleton file - this is where you will be placing your code for the competition.

The rules of Mastermind are as follows:
    A code master (which is the grading server) will select a peg sequence of n pegs, choosing from x
        colors (but never more than 9). The server reports to you how many pegs and colors it chose.
    The player (your program) submits a guess (in this case, by submitting a list of peg colors). Each color
        in your list represents a peg (submitting ["BLUE", "GREEN", "RED]" means you are saying the first peg is blue,
        the second is green, and the third is red.)
    The code master responds by telling the player how many of their peg guesses are correct in both color and position,
        and how many of their pegs are correct in color, but not position. Note that this response does not tell you 
        which pegs are correct - only how many. For example, if the code master chooses 
        ["BLUE", "BLUE", "GREEN", "PURPLE"] and you submit ["GREEN", "GREEN", "BLUE", "PURPLE"], the grader will respond
        by saying that one peg is correct in  color and position, and two pegs are correct in color, but not position.
 
@author <TODO: PLACE YOUR NAME HERE>
"""


def run_game(game):
    """
    Your code goes here. 
    Currently, the program guesses by cycling through the available color list.
    """

    # Get the number of pegs that were placed (the number of pegs you are trying to guess).
    number_of_pegs = game.number_of_pegs

    # Get the list of colors that the pegs might be.
    available_colors = game.available_colors

    # Get every possible solution for the given input
    all_possible_solutions = game.get_all_possible_codes()

    # Submission list. This is the peg color list that will be submitted - 
    # have your program place its peg guess here.
    mastermind_submission = []

    # Print them out for your reference - this is not necessary for your program to work.
    print('Number of pegs: ' + str(number_of_pegs))
    print('Peg Colors: ' + str(available_colors))
    print('All Possible codes: \n' + pprint.pformat(all_possible_solutions))

    # TODO: Add your logic here.
    # Currently, the program guesses by cycling through the available color list.
    #
    # Do NOT remove this while loop - your program will automatically terminate when it guesses correctly.
    while True:

        # START sample submission code
        color_to_pick = 0

        # Populate submission list (mastermindSubmission) by cycling through available colors
        # found in available_colors.
        for x in range(0, number_of_pegs):
            mastermind_submission.append(available_colors[color_to_pick])
            color_to_pick += 1

            # Cycle back to the start of the color list if we reached the end of it.
            if color_to_pick >= len(available_colors):
                color_to_pick = 0

        # Submit the mastermindSubmission list, which represents your peg guess.
        # Use this line of code to actually submit your guess
        mastermind_guess_response = game.request_mastermind_guess(mastermind_submission)

        # Access the submission response in order to get the following information:
        #  The number of pegs that are correct in position and color
        #  The number of pegs that are correct in color, but not position
        # The submission response also has a boolean that represents whether or not the guess was correct,
        # but your program will automatically be terminated upon a correct guess or if it reaches the max number 
        # of guesses (300), so you do not need to check it.
        print('Pegs correct in position and color: ' + str(mastermind_guess_response.correct_pegs))
        print('Pegs correct in position but not color: ' + str(mastermind_guess_response.correct_peg_colors))

        # Clear the submission list
        del mastermind_submission[:]


def main(_):
    """
    Responsible for starting the game server, connecting to it, and running the mastermind
    game besides your AI.

    DO NOT MODIFY MAIN. Modifying this method will result in your program not working and you getting a horrible score.
    """
    game = Game(sys.stdin, sys.stdout)
    sys.stdout = sys.stderr

    run_game(game)


if __name__ == "__main__":
    main(sys.argv)
