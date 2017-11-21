package game;

import java.io.BufferedReader;
import java.io.PrintStream;
import java.util.List;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

import json.Command;
import json.Message;
import json.PegColor;
import json.ReportNewGame;
import json.RequestMastermindGuess;
import json.MastermindGuessResponse;
import java.util.function.Predicate;
import java.util.*;
 

public class Game
{
    private final BufferedReader in;
    private final PrintStream out;
    private final JSONParser parser;
    private final PegColor[] colors;
    private final int pegs;
    private ArrayList<ArrayList<PegColor>> permutations = new ArrayList<ArrayList<PegColor>>(); 

    public Game (BufferedReader in, PrintStream out)
        throws Exception
    {
        this.in = in;
        this.out = out;
        this.parser = new JSONParser();

        ReportNewGame report = (ReportNewGame) this.readMessage();
        this.colors = report.getColors().toArray(new PegColor[0]);
        this.pegs = report.getNumberOfPegs();
    }

    public PegColor[] getColors()
    {
        return this.colors;
    }

    public int getNumberOfPegs()
    {
        return this.pegs;
    }

    public ArrayList<ArrayList<PegColor>> getAllPossibleCodes()
    {
        generatePermutations(new ArrayList<PegColor>(Arrays.asList(colors)), this.pegs, new ArrayList<PegColor>());
        return permutations;  
    }

    public MastermindGuessResponse requestMastermindGuess(List<PegColor> guessColors) throws Exception
    {
        RequestMastermindGuess request = new RequestMastermindGuess(guessColors);
        this.out.println(request.getJsonString());
        return (MastermindGuessResponse) this.readMessage();
    }

    private Message readMessage() throws Exception
	{
		String input = this.in.readLine();
		
		JSONObject jsonObject = (JSONObject) this.parser.parse(input);
		String commandString = (String) jsonObject.get("Command");
		
		Command commandType = Command.valueOf(commandString);
		switch (commandType)
		{
		case ReportNewGame:
			return new ReportNewGame(jsonObject);
        case MastermindGuessResponse:
			return new MastermindGuessResponse(jsonObject);
		default:
			throw new Exception("Unexpected command - " + commandString);
		}
    }
    
    private void generatePermutations(ArrayList<PegColor> input, int depth, ArrayList<PegColor> output) {
        if (depth == 0) {
            permutations.add(new ArrayList<PegColor>(output));
        } else {
            for (int i = 0; i < input.size(); i++) {
                output.add(input.get(i));
                generatePermutations(input, depth - 1, output);
                output.remove(output.size() - 1);
            }
        }
    }
}