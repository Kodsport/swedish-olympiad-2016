package parser;

import java.io.IOException;

public class State {
    public enum Direction {
        RIGHT, DOWN, LEFT, UP
    }

    private int x, y;
    private Direction dir;

    public State(int x, int y, Direction dir) throws IOException {
        this.x = x;
        this.y = y;
        this.dir = dir;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public Direction getDir() {
        return dir;
    }

}
