package json;

import java.util.List;
import java.util.ArrayList;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public class ReportNewGame implements Message
{
	private static final Command CommandType = Command.ReportNewGame;
    private final List<PegColor> colors;
    private final int pegs;
	
	public ReportNewGame(JSONObject reportNewGameObject)
	{
		JSONObject argsObject = (JSONObject) reportNewGameObject.get("Args");
        JSONArray colorsArray = (JSONArray) argsObject.get("ColorList");
        this.pegs = ((Long) argsObject.get("PegCount")).intValue();
        
		
		List<PegColor> availableColors = new ArrayList<PegColor>();
		for (Object col : colorsArray)
		{
			availableColors.add(PegColor.valueOf((String) col));
		}
		
		this.colors = availableColors;
	}
	
	@Override
	public Command getCommand()
	{
		return ReportNewGame.CommandType;
	}
	
	public List<PegColor> getColors()
	{
		return this.colors;
	}

	public int getNumberOfPegs()
	{
		return this.pegs;
	}
	
	@Override
	@SuppressWarnings("unchecked")
	public String getJsonString()
	{
		JSONObject reportNewGameObject = new JSONObject();
		JSONObject argsObject = new JSONObject();
		
		JSONArray colorsArray = new JSONArray();
		for (PegColor col : this.colors)
		{
			colorsArray.add(col.toString());
		}
		
        argsObject.put("ColorList", colorsArray);
        argsObject.put("Pegs", this.pegs);
		
		reportNewGameObject.put("Command", "ReportNewGame");
		reportNewGameObject.put("Args", argsObject);
		
		return reportNewGameObject.toJSONString();
	}
}