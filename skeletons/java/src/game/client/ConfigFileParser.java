package game.client;

import jdk.nashorn.internal.parser.JSONParser;

import org.json.JSONArray;
import org.json.JSONObject;

import org.json.simple.JSONParser;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Iterator;
import java.util.logging.Logger;


public class ConfigFileParser {
    public Object getProperty(String property) {
        Path currentPath = Paths.get(System.getProperty("user.dir"));
        Path configFilePath = Paths.get(currentPath.toString(), currentPath.getParent().toString(), "config.json");

        System.out.println(configFilePath.toString());

        JSONObject object=  new JSONObject()

        JSONParser parser = new JSONParser();

        Object returnObject = "Unknown Property Value";

        try {
            Object obj = parser.parse(new FileReader(configFilePath.toString()));

            JSONObject jsonObject = (JSONObject) obj;

            returnObject = jsonObject.get(property);

            Logger.getGlobal().finest("Read property from config file Property=" + property + ", Value=" + returnObject);
        } catch (FileNotFoundException e) {
            Logger.getGlobal().severe("Unable to open config file: ConfigFilePath=" + configFilePath);
        }

        return returnObject;
    }
}
