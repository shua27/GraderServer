
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
#include "src/json/json.hpp"
#include "src/game.h"

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

void runGame(GAME & game)
{
   // A list of all of the possible solutions, given this game board configuration.
   auto possibleCodes(game.getAllPossibleCodes());

   // Loop until the user has either guessed correctly or made some input error.
   while (!game.gameOver())
   {
      // TODO: Your code here!
      // Currently, the program guesses by cycling through the available color list.
      std::vector<std::string> guess;

      // Loop for game.getNumberOfPegs times. Populating a guess by cycling through the colors
      // available in game.getColors().
      uint32_t colorIndex = 0;
      for (uint32_t i = 0; i < game.getNumberOfPegs(); i++)
      {
         // Get a random color, add it to the guess.
         guess.push_back(game.getColors()[colorIndex++]);

         // Cycle back to the start of the color array if we reached the end of it.
         if (colorIndex >= game.getNumberOfPegs())
         {
            colorIndex = 0;
         }
      }

      // game.requestMastermindGuess is the function you'll call to make a move in the game.
      // This function takes a std::vector of std::strings which represents your (in-order) guess.
      // This function will return a MASTERMIND_GUESS_RESPONSE object which has information about
      // the number of correct pegs and the number of correct colors.
      auto mastermindGuessResponse(game.requestMastermindGuess(guess));

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
   GAME game(std::cin, std::cout, DEBUG_ENABLED);
   runGame(game);
   return EXIT_FAILURE;
}
