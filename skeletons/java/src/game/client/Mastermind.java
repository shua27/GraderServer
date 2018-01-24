package game.client;

import java.util.ArrayList;
import java.util.logging.Logger;

import org.json.JSONArray;
import org.json.JSONObject;

class Mastermind {
    private static final int PORT = 5000;
    private static final String URL = "127.0.0.1";

    private ArrayList<Integer> my_colors;
    private int my_peg_count;
    private ArrayList<ArrayList<Integer>> permutations = new ArrayList<>();

    private boolean gameOver = false;
    private static final Logger LOGGER = Logger.getLogger(Mastermind.class.getName());

    public ArrayList<ArrayList<Integer>> getAllPossibleCodes() {
        generatePermutations(this.my_colors, this.my_peg_count, new ArrayList<Integer>());
        return permutations;
    }

    public ArrayList<Integer> getColors() {
        return my_colors;
    }

    public boolean gameOver() {
        return this.gameOver;
    }

    public boolean requestMastermindGuess(ArrayList<Integer> guess) {
//        JSONObject requestResponse = this.my_client.getJson("";)

        //        RequestMastermindGuess request = new RequestMastermindGuess(guess);
        //        System.out.println(request.getJsonString());
        //        return (MastermindGuessResponse) this.readMessage();
        return false;
    }

    private Client my_client;


    Mastermind() {
        this.my_client = new Client(URL, PORT);
        this.my_colors = new ArrayList<>();

        JSONObject gameStartData = this.my_client.getJson("CreateChallenge").getBody().getObject();

        String command = gameStartData.getString("Command");
        JSONObject args = gameStartData.getJSONObject("Args");

        LOGGER.info("Game starting data received: ReceivedJSON=" + gameStartData.toString());

        JSONArray jsonArray = args.getJSONArray("ColorList");

        for (Object obj : jsonArray) {
            this.my_colors.add((Integer) obj);
        }

        this.my_peg_count = args.getInt("PegCount");
    }

    /**
     * Implementation of private methods.
     *
     * @param input  The list of pegs
     * @param depth  The current recursion depth. Starts at number of pegs and decreases to 0ish.
     * @param output A poorly name param?
     */
    private void generatePermutations(ArrayList<Integer> input, int depth, ArrayList<Integer> output) {
        if (depth == 0) {
            permutations.add(new ArrayList<Integer>(output));
        } else {
            for (int i = 0; i < input.size(); i++) {
                output.add(input.get(i));
                generatePermutations(input, depth - 1, output);
                output.remove(output.size() - 1);
            }
        }
    }

}
