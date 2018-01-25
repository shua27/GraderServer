package game.client;

import java.nio.file.FileSystem;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.logging.Level;
import java.util.logging.Logger;

public class GameLogging {
    public void initialze(){
        Logger logger = Logger.getGlobal();
        logger.setLevel(Level.ALL);
    }


    public GameLogging() {
        this.initialze();
    }
}
