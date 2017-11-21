package json;

import java.util.List;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public class RequestMastermindGuess implements Message
{
    private static final Command CommandType = Command.RequestMastermindGuess;
    private final List<PegColor> guessColors;
	
	public RequestMastermindGuess(List<PegColor> guessColors)
	{
		// JSONObject argsObject = (JSONObject) requestMastermindGuessObject.get("Args");
        // JSONArray colorGuess = (JSONArray) argsObject.get("ColorList");
        	
		// List<PegColor> submitted = new ArrayList<PegColor>();
		// for (Object col : colorGuess)
		// {
		// 	colorGuess.add(PegColor.valueOf((String) col));
		// }
		
		this.guessColors = guessColors;
	}
	
	@Override
	public Command getCommand()
	{
		return RequestMastermindGuess.CommandType;
	}
	
	public List<PegColor> getColors()
	{
		return this.guessColors;
	}
	
	@Override
	@SuppressWarnings("unchecked")
	public String getJsonString()
	{
        JSONObject requestMastermindGuessObject = new JSONObject();
		JSONObject argsObject = new JSONObject();
		
		JSONArray colorsArray = new JSONArray();
		for (PegColor col : this.guessColors)
		{
			colorsArray.add(col.toString());
		}
		
        argsObject.put("BoardRow", colorsArray);
		
		requestMastermindGuessObject.put("Command", "RequestMastermindGuess");
		requestMastermindGuessObject.put("Args", argsObject);
		
        return requestMastermindGuessObject.toJSONString();
	}
}