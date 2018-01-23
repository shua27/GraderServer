package game.client;

import com.mashape.unirest.http.HttpResponse;
import com.mashape.unirest.http.JsonNode;
import com.mashape.unirest.http.Unirest;
import com.mashape.unirest.http.exceptions.UnirestException;

import java.util.ArrayList;

public class Client {

    private final String PROTOCOL = "http://";
    private String my_url;
    private int my_port;
    private final String GAME_IDENT = "Mastermind";

    private String makeFullURL(String suffix) {
        return PROTOCOL + my_url + ':' + my_port + '/' + GAME_IDENT + '/' + suffix;
    }

    Client(String url, int port) {
        this.my_url = url;
        this.my_port = port;
    }

    public HttpResponse<JsonNode> getJson(String urlSuffix) {
        try {
            return Unirest.get(this.makeFullURL(urlSuffix)).header("accept", "application/json").asJson();
        } catch (UnirestException e) {
            e.printStackTrace();
        }

        return null;
    }
}


//    public static void connect(String url) throws UnirestException {
//        HttpResponse<JsonNode> jsonResponse = Unirest.post("http://httpbin.org/post")
//                .header("accept", "application/json")
//                .queryString("apiKey", "123")
//                .field("parameter", "value")
//                .field("foo", "bar")
//                .asJson();