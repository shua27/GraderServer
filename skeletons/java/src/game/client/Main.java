package game.client;

import java.io.*;
import java.net.*;

public class Main {

    public static String getHTML(String urlToRead) throws Exception {
        StringBuilder result = new StringBuilder();
        URL url = new URL(urlToRead);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");

        BufferedReader rd = new BufferedReader(new InputStreamReader(conn.getInputStream()));

        String line;
        while ((line = rd.readLine()) != null) {
            result.append(line);
        }
        rd.close();

        return result.toString();
    }

    public static void main(String[] args) throws Exception{

        System.out.println(getHTML("http://127.0.0.1"));

        System.out.println("Hello world");
    }
}
