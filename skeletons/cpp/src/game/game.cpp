/**
 * @file game.h
 * @brief Definition of the game class for mastermind.
 */

/*
 * ========================================================================
 * Includes
 * ========================================================================
 */

#include <algorithm>
#include "json/json.hpp"
#include "game.h"
#include "utilities.h"

/*
 * ========================================================================
 * Constants
 * ========================================================================
 */

namespace
{
constexpr auto COMMAND_KEY = "Command";

}   // namespace

/*
 * ========================================================================
 * Implementation
 * ========================================================================
 */

GAME::GAME(std::istream & inputStream, std::ostream & outputStream, bool debugEnabled)
   : my_input_stream(inputStream), my_output_stream(outputStream), my_debug_enabled(debugEnabled)
{
   // Get a line from the input stream. This line should be the report to start a new game.
   std::string string;
   std::getline(this->my_input_stream, string);

   // Parse the line as JSON.
   auto json(nlohmann::json::parse(string));

   // Check that the received command is indeed the report to start a new game.
   if (json[COMMAND_KEY] == "ReportNewGame")
   {
      // Populate member data about the new game.
      auto reportNewGameCommand(REPORT_NEW_GAME_COMMAND::fromJson(json));
      this->my_number_of_pegs = reportNewGameCommand.numberOfPegs;
      this->my_color_choices = reportNewGameCommand.colors;

      if (debugEnabled)
      {
         std::cerr << "Received: " << json << '\n';
         std::cerr << "New game: Number of Pegs = " << this->getNumberOfPegs() << '\n';
         std::cerr << "Available Colors = ";
         util::streamContainerElements(std::cerr, this->getColors());
      }
   }
   else
   {
      std::cerr
         << "Unexpected command while constructing game: Expected={ReportStartGame}, Received={"
         << json[COMMAND_KEY] << "}" << std::endl;
      this->my_game_over = true;
   }
}

MASTERMIND_GUESS_RESPONSE GAME::requestMastermindGuess(std::vector<std::string> const & guess)
{
   auto correct(false);
   uint32_t numCorrect(0);
   uint32_t numColorcorrect(0);

   // First, check that we're guessing the correct number of pegs.
   if (guess.size() == this->my_number_of_pegs)
   {
      auto guessJson(REQUEST_MASTERMIND_GUESS_COMMAND(guess).json);

      // Print the guess if we're debugging.
      if (this->my_debug_enabled)
      {
         std::cerr << "Guessing " << guessJson << std::endl;
      }

      this->my_output_stream << guessJson << std::endl << std::flush;

      // Get a line (the response) from the input stream.
      std::string string;
      std::getline(this->my_input_stream, string);

      // Print the response if we're debugging.
      if (this->my_debug_enabled)
      {
         std::cerr << "Response received " << string << std::endl;
      }

      // Parse the line as a JSON object.
      auto json(nlohmann::json::parse(string));

      if (json[COMMAND_KEY] == "MastermindGuessResponse")
      {
         auto mastermindGuessResponse(MASTERMIND_GUESS_RESPONSE::fromJson(json));
         correct = mastermindGuessResponse.correct;
         numCorrect = mastermindGuessResponse.correctCount;
         numColorcorrect = mastermindGuessResponse.correctPegColors;
      }
      else
      {
         std::cerr << "Unexpected command while constructing game: "
                      "Expected={MastermindGuessResponse}, Received={"
                   << json[COMMAND_KEY] << "}" << std::endl;
         this->my_game_over = true;
      }
   }
   else
   {
      // Print an error if we've guessed the wrong number of pegs.
      std::cerr << "Wrong number of pegs: GuessProvided=";
      util::streamContainerElements(std::cerr, guess);
      this->my_game_over = true;
   }
   return {correct, numCorrect, numColorcorrect};
}

POSSIBLE_CODES_TYPE GAME::makePermutationsOfSets(POSSIBLE_CODES_TYPE const & inputSet) const
{
   POSSIBLE_CODES_TYPE outputSet;
   for (auto permutatedVector : inputSet)
   {
      std::sort(permutatedVector.begin(), permutatedVector.end());
      do
      {
         outputSet.push_back(permutatedVector);
      } while (std::next_permutation(permutatedVector.begin(), permutatedVector.end()));
   }

   return outputSet;
}

void GAME::addVectorToSet(
   POSSIBLE_CODES_TYPE & outputSet,
   std::vector<uint32_t> const & indexVector,
   std::vector<std::string> const & availableColors) const
{
   std::vector<std::string> vectorToAddToSet;

   for (uint32_t i = 0; i < indexVector.size() - 1; i++)
   {
      vectorToAddToSet.push_back(availableColors[indexVector.at(i)]);
   }
   outputSet.push_back(vectorToAddToSet);
}

POSSIBLE_CODES_TYPE GAME::getAllPossibleCodes() const
{
   POSSIBLE_CODES_TYPE comboSet;
   auto numberOfColors(this->my_color_choices.size());
   numberOfColors--;
   std::vector<uint32_t> indexVector(this->my_number_of_pegs + 1, 0);

   while (true)
   {
      for (uint32_t i = 0; i < this->my_number_of_pegs; ++i)
      {
         if (indexVector[i] > numberOfColors)
         {
            indexVector[i + 1] += 1;
            for (int k = i; k >= 0; --k)
            {
               indexVector[k] = indexVector[i + 1];
            }
         }
      }

      if (indexVector[this->my_number_of_pegs] > 0)
      {
         break;
      }

      this->addVectorToSet(comboSet, indexVector, this->my_color_choices);
      indexVector[0] += 1;
   }

   auto outputSet(makePermutationsOfSets(comboSet));

   if (this->my_debug_enabled)
   {
      std::cerr << "Built container: Size=" << outputSet.size() << "\n";
      util::streamContainerContainerElements(std::cerr, outputSet);
   }
   return outputSet;
}

