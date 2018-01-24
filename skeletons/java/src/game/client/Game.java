package game.client;

public class Game {
    private Client my_client;

    public Game(String url, int port) {
        this.my_client = new Client(url, port);
    }
}
