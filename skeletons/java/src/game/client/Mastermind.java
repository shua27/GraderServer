package game.client;


import com.mashape.unirest.http.HttpResponse;
import com.mashape.unirest.http.JsonNode;

class Mastermind {
    private static final int PORT = 5000;
    private static final String URL = "127.0.0.1";

    private Client my_client;

    Mastermind() {
        this.my_client = new Client(URL, PORT);
        HttpResponse<JsonNode> gameStartData = this.my_client.getJson("CreateChallenge");

        System.out.println(gameStartData.getBody());
    }
}
