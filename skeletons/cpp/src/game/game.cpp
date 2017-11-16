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
#include <cpr/cpr.h>
#include <json.hpp>
#include "game.h"
#include "utilities.h"
#include "mastermind-commands.h"

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

GAME::GAME(std::string const & url, uint32_t port, bool debugEnabled)
   : my_socket_address(url + "/" + std::to_string(port)), my_debug_enabled(debugEnabled)
{
   REQUEST_MASTERMIND_GUESS_COMMAND command{{"BLUE", "GREEN", "RED"}};

   std::cout << "commandjson = " <<  command.json << "\n";

   // Parse the line as JSON.
   auto response(cpr::Get(cpr::Url{"http://127.0.0.1:5000/CreateChallenge/1"}));

   if (!response.error)
   {
      auto responseAsJson(nlohmann::json::parse(response.text));

      std::cout << "Received the following Json from the GraderServer: {" << responseAsJson << "}\n";

      // Check that the received command is indeed the report to start a new game.
      if (responseAsJson[COMMAND_KEY] == "ReportNewGame")
      {
         // Populate member data about the new game.
         auto reportNewGameCommand(REPORT_NEW_GAME_COMMAND::fromJson(responseAsJson));
         this->my_number_of_pegs = reportNewGameCommand.numberOfPegs;
         this->my_color_choices = reportNewGameCommand.colors;

         if (debugEnabled)
         {
            std::cerr << "Received: " << responseAsJson << '\n';
            std::cerr << "New game: Number of Pegs = " << this->getNumberOfPegs() << '\n';
            std::cerr << "Available Colors = ";
            util::streamContainerElements(std::cerr, this->getColors());
         }
      }
      else
      {
         std::cerr << "Unexpected command while constructing game: Expected={ReportStartGame}, Received={"
                   << responseAsJson[COMMAND_KEY] << "}" << std::endl;
         this->my_game_over = true;
      }
   }
   else
   {
      std::cerr << "Failed connecting to game server";
   }
}

MASTERMIND_GUESS_RESPONSE GAME::requestMastermindGuess(std::vector<std::string> const & guess)
{
   auto correct(false);
   uint32_t numCorrect(0);
   uint32_t numColorCorrect(0);

   // First, check that we're guessing the correct number of pegs.
   auto guessJson(REQUEST_MASTERMIND_GUESS_COMMAND(guess).json);

   // Print the guess if we're debugging.
   if (this->my_debug_enabled)
   {
      std::cerr << "Guessing " << guessJson << std::endl;
   }

   // TODO : Send the guess to the server
   //      this->my_output_stream << guessJson << std::endl << std::flush;

   // TODO: Get a response from the server
   //      std::string string;
   //      std::getline(this->my_input_stream, string);

   // Print the response if we're debugging.

   // Parse the line as a JSON object.

   std::string string = "Blah";
   assert(false);   // We expect to fail for now, that's okay.
   auto json(nlohmann::json::parse(string));

   if (json[COMMAND_KEY] == "MastermindGuessResponse")
   {
      auto mastermindGuessResponse(MASTERMIND_GUESS_RESPONSE::fromJson(json));
      correct = mastermindGuessResponse.correct;
      numCorrect = mastermindGuessResponse.correctCount;
      numColorCorrect = mastermindGuessResponse.correctPegColors;
   }
   else
   {
      std::cerr << "Unexpected command while constructing game: "
                   "Expected={MastermindGuessResponse}, Received={"
                << json[COMMAND_KEY] << "}" << std::endl;
      this->my_game_over = true;
   }

   return {correct, numCorrect, numColorCorrect};
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
