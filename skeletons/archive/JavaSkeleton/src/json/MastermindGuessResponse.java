package json;

import org.json.simple.JSONObject;

public class MastermindGuessResponse implements Message
{
    private static final Command CommandType = Command.MastermindGuessResponse;
    private final boolean isCorrect;
    private final int correctPegs;
    private final int correctPegColors;

    public MastermindGuessResponse(JSONObject guessResponseObject)
    {
        JSONObject argsObject = (JSONObject) guessResponseObject.get("Args");
        this.isCorrect = (boolean) argsObject.get("Correct");
        this.correctPegs = ((Long) argsObject.get("CorrectPegs")).intValue();
        this.correctPegColors = ((Long) argsObject.get("CorrectPegColors")).intValue();
    }

    @Override
    public Command getCommand()
    {
        return MastermindGuessResponse.CommandType;
    }

    public boolean isCorrect()
    {
        return this.isCorrect;
    }

    public int getCorrectPegs()
    {
        return this.correctPegs;
    }

    public int getCorrectPegColors()
    {
        return this.correctPegColors;
    }

    @Override
	@SuppressWarnings("unchecked")
	public String getJsonString()
	{
		JSONObject guessResponseObject = new JSONObject();
		JSONObject argsObject = new JSONObject();
		
		argsObject.put("Correct", this.isCorrect);
        argsObject.put("CorrectPegs", this.correctPegs);
        argsObject.put("CorrectPegColors", this.correctPegColors);
		
		guessResponseObject.put("Command", "MastermindGuessResponse");
		guessResponseObject.put("Args", argsObject);
		
		return guessResponseObject.toJSONString();
	}
}