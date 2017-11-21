
/**
 * @file main.cpp
 * @brief This file is your skeleton file - this is where you will be placing your code for the
 * competition.
 *
 * The rules of Mastermind are as follows:
 *  A code master (which is the grading server) will select a peg sequence of n pegs, choosing from
 *      x colors (but never more than 9). The server reports to you how many pegs and colors it
 *      chose.
 *
 *  The player (your program) submits a guess (in this case, by submitting a list of peg colors).
 *      Each color in your list represents a peg (submitting ["BLUE", "GREEN", "RED]" means you are
 *      saying the first peg is blue, the second is green, and the third is red.)
 *
 *  The code master responds by telling the player how many of their peg guesses are correct in both
 *      color and position, and how many of their pegs are correct in color, but not position. Note
 *      that this response does not tell you which pegs are correct - only how many. For example, if
 *      the code master chooses ["BLUE", "BLUE", "GREEN", "PURPLE"] and you submit
 *      ["GREEN", "GREEN", "BLUE", "PURPLE"], the grader will repsond by saying that one peg is
 *      correct in color and position, and two pegs are correct in color, but not position.
 */

/*
 * ========================================================================
 * Includes
 * ========================================================================
 */

#include <iostream>
#include "json.hpp"
#include "game/game.h"

/*
 * ========================================================================
 * Constants
 * ========================================================================
 */

namespace
{
constexpr bool DEBUG_ENABLED = true;   // Set to true to print debug messages .
}   // namespace

/*
 * ========================================================================
 * Contestant Code
 * ========================================================================
 */

MASTERMIND_GUESS_RESPONSE testCodeAgainstGuess(
   std::vector<COLOR_TYPE> const & codeIn,
   std::vector<COLOR_TYPE> const & guessIn)
{
   auto code(codeIn);
   auto guess(guessIn);
   uint32_t numCorrect(0);
   uint32_t numColorCorrect(0);

   std::vector<std::uint32_t> indexesToErase;

   for (uint32_t i = 0; i < code.size(); i++)
   {
      if (code[i] == guess[i])
      {
         numCorrect++;
         code[i] = 0;
         guess[i] = 0;
      }
   }

   code.erase(
      std::remove_if(
         code.begin(), code.end(), [](COLOR_TYPE const & color) { return color == 0; }),
      code.end());

   guess.erase(
      std::remove_if(
         guess.begin(), guess.end(), [](COLOR_TYPE const & color) { return color == 0; }),
      guess.end());

   while (!guess.empty())
   {
      auto color(guess.back());
      guess.pop_back();

      auto it = std::find(code.begin(), code.end(), color);

      if (it != code.end())
      {
         numColorCorrect++;
         code.erase(it);
      }
   }

   return {false, numCorrect, numColorCorrect};
}

void filterCodes(
   std::vector<COLOR_TYPE> const & guess,
   MASTERMIND_GUESS_RESPONSE const & response,
   POSSIBLE_CODES_TYPE & currentPossibilities)
{
   currentPossibilities.erase(
      std::remove_if(
         currentPossibilities.begin(),
         currentPossibilities.end(),
         [&guess, &response](std::vector<COLOR_TYPE> const & code) {
            bool sameAnswer(testCodeAgainstGuess(code, guess) == response);
            return !sameAnswer;
         }),
      currentPossibilities.end());
}

void runGame(GAME & game)
{
   // A list of all of the possible solutions, given this game board configuration.
   auto possibleCodes(game.getAllPossibleCodes());

   auto colors(game.getColors());

   // Loop until the user has either guessed correctly or made some input error.
   while (!game.gameOver())
   {
      // TODO: Your code here!
      // Currently, the program guesses by cycling through the available color list.
      auto guess(possibleCodes.back());
      possibleCodes.pop_back();

      auto mastermindGuessResponse(game.requestMastermindGuess(guess));

      filterCodes(guess, mastermindGuessResponse, possibleCodes);

      // Access the submission response in order to get the following information:
      //  The number of pegs that are correct in position and color
      //  The number of pegs that are correct in color, but not position
      // The submission response also has a boolean that represents whether or not the guess was
      // correct, but your program will automatically be terminated upon a correct guess or if it
      // reaches the max number of guesses (300), so you do not need to check it.
      if (DEBUG_ENABLED)
      {
         std::cerr << "Number correct = " << mastermindGuessResponse.correctCount << std::endl;
         std::cerr << "Color Correct = " << mastermindGuessResponse.correctPegColors << std::endl;
      }
   }
}

/**
 * ========================================================================
 * Main
 * ========================================================================
 * Responsible for starting the game server, connecting to it, and running the mastermind game
 * against your AI.
 *
 * DO NOT MODIFY MAIN.
 *
 * Modifying this method will result in your program not working and you getting a horrible score.
 * ========================================================================
 */
int main()
{
   GAME game("127.0.0.1", 5000, DEBUG_ENABLED);
   runGame(game);
   return EXIT_FAILURE;
}
