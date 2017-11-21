from __future__ import print_function

import itertools
import json


class Game:
    def __init__(self, reader, writer):
        self._in = reader
        self._out = writer

        report_new_game = self.__read_message()
        self._availableColors = report_new_game["Args"]["ColorList"]
        self._numberOfPegs = report_new_game["Args"]["PegCount"]

    @property
    def available_colors(self):
        return self._availableColors

    @property
    def number_of_pegs(self):
        return self._numberOfPegs

    def request_mastermind_guess(self, pegs_to_guess):
        """
        Will send the peg guess to the code master.
        Returns a MastermindGuessResponse object.
        """
        request = {"Command": "RequestMastermindGuess", "Args": {"BoardRow": pegs_to_guess}}
        self.__send_mesage(request)
        response = self.__read_message()
        return MastermindGuessResponse(response["Args"]["Correct"], response["Args"]["CorrectPegs"],
                                       response["Args"]["CorrectPegColors"])

    def get_all_possible_codes(self):
        return list(itertools.product(self._availableColors, repeat=self.number_of_pegs))

    def __send_mesage(self, message):
        print(json.dumps(message), file=self._out)
        self._out.flush()

    def __read_message(self):
        response = json.loads(self._in.readline())
        return response


class MastermindGuessResponse:
    def __init__(self, is_correct, correct_pegs, correct_color_pegs):
        self._isCorrect = is_correct
        self._correctPegs = correct_pegs
        self._correctPegColors = correct_color_pegs

    @property
    def is_correct(self):
        return self._isCorrect

    @property
    def correct_pegs(self):
        return self._correctPegs

    @property
    def correct_peg_colors(self):
        return self._correctPegColors
