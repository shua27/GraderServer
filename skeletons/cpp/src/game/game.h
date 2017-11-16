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
#include "mastermind-commands.h"

/*
 * ========================================================================
 * Aliases
 * ========================================================================
 */

using POSSIBLE_CODES_TYPE = std::vector<std::vector<uint32_t>>;

/*
 * ========================================================================
 * Class Definitions
 * ========================================================================
 */

class GAME final
{
private:
   const std::string my_socket_address;

   uint32_t my_number_of_pegs;
   std::vector<uint32_t> my_color_choices;
   bool my_game_over = false;
   bool my_debug_enabled = false;

   POSSIBLE_CODES_TYPE makePermutationsOfSets(POSSIBLE_CODES_TYPE const & inputSet) const;

   void addVectorToSet(
      POSSIBLE_CODES_TYPE & outputSet,
      std::vector<uint32_t> const & indexVector,
      std::vector<uint32_t> const & availableColors) const;

public:
   GAME() = delete;
   GAME(GAME const &) = delete;
   GAME & operator=(GAME const &) = delete;

   GAME(std::string const & url, uint32_t port, bool debugEnabled);

   inline std::vector<uint32_t> getColors()
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

   MASTERMIND_GUESS_RESPONSE requestMastermindGuess(std::vector<uint32_t> const & guess);

   POSSIBLE_CODES_TYPE getAllPossibleCodes() const;
};

#endif   // CPPSKELETON_GAME_H
