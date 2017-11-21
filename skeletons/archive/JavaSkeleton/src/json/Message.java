package json;

public interface Message
{
	Command getCommand();
	
	String getJsonString();
}