/**
 * @file game.h
 * @brief Definition of the GAME class for mastermind.
 */

#ifndef CPPSKELETON_GAME_H
#define CPPSKELETON_GAME_H

/*
 * ========================================================================
 * Includes
 * ========================================================================
 */

#include <vector>
#include <iostream>
#include <cstdint>
#include "commands/mastermind-commands.h"

/*
 * ========================================================================
 * Aliases
 * ========================================================================
 */

using POSSIBLE_CODES_TYPE = std::vector<std::vector<std::string>>;

/*
 * ========================================================================
 * Class Definitions
 * ========================================================================
 */

class GAME final
{
private:
   std::istream & my_input_stream;
   std::ostream & my_output_stream;
   uint32_t my_number_of_pegs;
   std::vector<std::string> my_color_choices;
   bool my_game_over = false;
   bool my_debug_enabled = false;

   POSSIBLE_CODES_TYPE makePermutationsOfSets(POSSIBLE_CODES_TYPE const & inputSet) const;

   void addVectorToSet(
      POSSIBLE_CODES_TYPE & outputSet,
      std::vector<uint32_t> const & indexVector,
      std::vector<std::string> const & availableColors) const;

public:
   GAME() = delete;
   GAME(GAME const &) = delete;
   GAME & operator=(GAME const &) = delete;

   GAME(std::istream & inputStream, std::ostream & outputStream, bool debugEnabled);

   inline std::vector<std::string> getColors()
   {
      return this->my_color_choices;
   }

   inline uint32_t getNumberOfPegs()
   {
      return this->my_number_of_pegs;
   }

   inline bool gameOver()
   {
      return this->my_game_over;
   }

   MASTERMIND_GUESS_RESPONSE requestMastermindGuess(std::vector<std::string> const & guess);

   POSSIBLE_CODES_TYPE getAllPossibleCodes() const;
};

#endif   // CPPSKELETON_GAME_H