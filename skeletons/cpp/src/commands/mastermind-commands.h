/**
 * @file mastermind-commands.h
 * @brief
 * @addtogroup
 * @{
 */
#ifndef CPPSKELETON_MASTERMIND_COMMANDS_H
#define CPPSKELETON_MASTERMIND_COMMANDS_H

/*
 * ========================================================================
 * Includes
 * ========================================================================
 */

#include "json.hpp"

/*
 * ========================================================================
 * Constants
 * ========================================================================
 */

namespace
{
constexpr auto ARGS_KEY = "Args";
}   // namespace

/*
 * ========================================================================
 * Class Definitions
 * ========================================================================
 */

/**
 * @brief Received command which contains information about a new game.
 */
struct REPORT_NEW_GAME_COMMAND final
{
   REPORT_NEW_GAME_COMMAND() = delete;
   const uint32_t numberOfPegs;
   const std::vector<uint32_t> colors;

   static constexpr auto COLOR_KEY = "ColorList";
   static constexpr auto PEG_KEY = "PegCount";

   static inline REPORT_NEW_GAME_COMMAND fromJson(nlohmann::json const & json)
   {
      auto args(json[ARGS_KEY]);

      uint32_t pegCount(args[PEG_KEY]);
      std::vector<uint32_t> colors;

      for (auto const & color : args[COLOR_KEY])
      {
         colors.push_back(color);
      }

      return {pegCount, colors};
   }
};

/**
 * @brief Command to send to the server to specify a guess.
 */
struct REQUEST_MASTERMIND_GUESS_COMMAND final
{
   REQUEST_MASTERMIND_GUESS_COMMAND() = delete;
   nlohmann::json json;

   explicit REQUEST_MASTERMIND_GUESS_COMMAND(std::vector<uint32_t> const & guess)
   {
      this->json = {{"Args", {{"BoardRow", guess}}}, {"Command", "RequestMastermindGuess"}};
   }
};

/**
 * @brief Received command which contains information about a new game.
 */
struct MASTERMIND_GUESS_RESPONSE final
{
   MASTERMIND_GUESS_RESPONSE() = delete;
   const bool correct;
   const uint32_t correctCount;
   const uint32_t correctPegColors;

   static constexpr auto CORRECT_KEY = "Correct";
   static constexpr auto CORRECT_COUNT_KEY = "CorrectPegs";
   static constexpr auto CORRECT_PEG_COLORS_KEY = "CorrectPegColors";

   static inline MASTERMIND_GUESS_RESPONSE fromJson(nlohmann::json const & json)
   {
      auto args(json[ARGS_KEY]);

      return {args[CORRECT_KEY], args[CORRECT_COUNT_KEY], args[CORRECT_PEG_COLORS_KEY]};
   }

   inline bool operator==(const MASTERMIND_GUESS_RESPONSE & other)
   {
      return this->correctCount == other.correctCount &&
             this->correctPegColors == other.correctPegColors;
   }
};

/**
 * @brief Received command which contains information about a new game.
 */
struct MASTERMIND_GAME_OVER_REPORT final
{
   MASTERMIND_GAME_OVER_REPORT() = delete;
   const bool correct;
   const uint32_t guessCount;

   static inline MASTERMIND_GAME_OVER_REPORT fromJson(nlohmann::json const & json)
   {
      auto args(json[ARGS_KEY]);

      return {args["Correct"], args["GuessCount"]};
   }
};

#endif   // CPPSKELETON_MASTERMIND_COMMANDS_H

/**
 * @}
 */
