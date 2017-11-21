package main;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;
import java.util.*;


import game.Game;
import json.MastermindGuessResponse;
import json.PegColor;

/**
 * This file is your skeleton file - this is where you will be placing your code for the competition.
 * 
 * The rules of Mastermind are as follows:
 *  A code master (which is the grading server) will select a peg sequence of n pegs, choosing from x
 *      colors (but never more than 9). The server reports to you how many pegs and colors it chose.
 *  The player (your program) submits a guess (in this case, by submitting a list of peg colors). Each color
 *      in your list represents a peg (submitting ["BLUE", "GREEN", "RED]" means you are saying the first peg is blue,
 *      the second is green, and the third is red.)
 *  The code master responds by telling the player how many of their peg guesses are correct in both color and position,
 *      and how many of their pegs are correct in color, but not position. Note that this response does not tell you which
 *      pegs are correct - only how many. For example, if the code master chooses ["BLUE", "BLUE", "GREEN", "PURPLE"] and
 *      you submit ["GREEN", "GREEN", "BLUE", "PURPLE"], the grader will repsond by saying that one peg is correct in 
 *      color and position, and two pegs are correct in color, but not position.
 * 
 * @author <TODO: PLACE YOUR NAME HERE>
 */

public class Main
{

    /**
     * Responsible for starting the game server, connecting to it, and running the mastermind
     * game besides your AI. 
     * 
     * DO NOT MODIFY MAIN. Modifying this method will result in your program not working and you getting a horrible score.
     */
    public static void main (String args[]) throws Exception
    {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        Game game = new Game(reader, System.out);
        System.setOut(System.err);
        runGame(game);
    }

    /**
     * Method responsible for interacting with the mastermind server.
     * 
     * PEG GUESSES: Guesses for the row of pegs in mastermind are made by creating an array of peg
     * colors from the PegColor enum. This submission array is NOT an array of strings - it must use 
     * colors from the PegColor enum. All available colors can be accessed in the <code>availableColors</code>
     * array.
     * 
     */
    public static void runGame(Game game) throws Exception
    {
        // Get the number of pegs that were placed (the number of pegs you are trying to guess).
        int numberOfPegs = game.getNumberOfPegs();

        // Get the list of colors that the pegs might be.
        PegColor[] availableColors = game.getColors();

        // Submission array. This is the peg color array that will be submitted - 
        // have your program place its peg guess here.
        PegColor[] mastermindSubmission = new PegColor[numberOfPegs];

        // Print them out for your refernce - this is not necessary for your program to work.
        System.out.printf("Number of pegs: %d%n", numberOfPegs);
        System.out.printf("Peg Colors: %s%n", Arrays.toString(availableColors));



        // TODO: Add your logic here.
        // Currently, the program guesses by cycling through the available color list.
        //
        // Do NOT remove this while loop - your program will automatically terminate when it guesses correctly.
        while(true)
        {
            // START sample submission code
            int colorToPick = 0;

            // Populate submission array (<code>mastermindSubmission</code>) by cycling through available colors
            // found in <code>availableColors</code>.
            for (int i = 0; i < mastermindSubmission.length; i++)
            {
                mastermindSubmission[i] = availableColors[colorToPick];
                colorToPick++;

                // Cycle back to the start of the color array if we reached the end of it.
                if (colorToPick >= availableColors.length)
                {
                    colorToPick = 0;
                }
            }

            // END sample submission code

            // Submit the mastermindSubmission array, which represents your peg guess.
            // Use this line of code to actually submit your guess. Also, the submission has to be a list, so make
            // sure to use <code>Arrays.asList(mastermindSubmission)<\code>
            MastermindGuessResponse mastermindGuessResponse = game.requestMastermindGuess(Arrays.asList(mastermindSubmission));

            // Access the submission response in order to get the following information:
            //  The number of pegs that are correct in position and color
            //  The number of pegs that are correct in color, but not position
            // The submission response also has a boolean that represents whether or not the guess was correct,
            // but your program will automatically be terminated upon a correct guess or if it reaches the max number 
            // of guesses (300), so you do not need to check it.
            System.out.printf("Pegs correct in position and color: %d%n", mastermindGuessResponse.getCorrectPegs());
            System.out.printf("Pegs correct in position but not color: %d%n%n", mastermindGuessResponse.getCorrectPegColors());
        }
    }
}