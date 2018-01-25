package game.client;

import java.util.ArrayList;

public class Main {

    private static void setLoggingLevel(){

    }

    private static void playGame(Mastermind game) {
        // A list of all of the possible solutions, given this game board configuration.
        ArrayList<ArrayList<Integer>> possibleCodes = game.getAllPossibleCodes();

        ArrayList<Integer> colors = game.getColors();

        // Loop until the user has either guessed correctly or made some input error.
        while (!game.gameOver() && !possibleCodes.isEmpty()) {
            // TODO: Your code here!
            // Currently, the program guesses by cycling through the available color list.
            ArrayList<Integer> guess = possibleCodes.remove(0);

            boolean mastermindGuessResponse  = game.requestMastermindGuess(guess);

            // Access the submission response in order to get the following information:
            //  The number of pegs that are correct in position and color
            //  The number of pegs that are correct in color, but not position
            // The submission response also has a boolean that represents whether or not the guess was
            // correct, but your program will automatically be terminated upon a correct guess or if it
            // reaches the max number of guesses (300), so you do not need to check it.
//            System.out.println("Number correct = " + mastermindGuessResponse.correctCount);
//            System.out.println("Color correct = " + mastermindGuessResponse.correctPegColors);
        }

    }

    public static void main(String[] args) throws Exception {
        GameLogging logger = new GameLogging();

        Mastermind game = new Mastermind();
        playGame(game);
    }
}
