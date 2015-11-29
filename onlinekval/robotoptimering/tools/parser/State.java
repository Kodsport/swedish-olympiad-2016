package parser;

public class State implements Cloneable {
    public enum Direction {
        RIGHT, DOWN, LEFT, UP
    }

    private int row, col;
    private Direction dir;
    private int line;
    private boolean isWinningPosition = false;

    public State(int x, int y, Direction dir) {
        this.row = x;
        this.col = y;
        this.dir = dir;
        line = 0;
    }

    public int getRow() {
        return row;
    }

    public int getCol() {
        return col;
    }

    public Direction getDir() {
        return dir;
    }

    public int getLine() { return line; }

    /**
     * Get the angle in radians for the robot.
     */
    public double getAngle() {
        switch (dir) {
            case RIGHT:
                return -Math.PI / 2;
            case UP:
                return 0;
            case DOWN:
                return Math.PI;
            case LEFT:
                return -Math.PI / 2;
            default:
                throw new IllegalStateException("Unknown direciton");
        }
    }

    public void updateDir(Direction dir, int line) {
        this.dir = dir;
        this.line = line;
    }

    public void updatePos(int row, int col, int line) {
        this.row = row;
        this.col = col;
        this.line = line;
    }

    public void setAsWinningState() {
        isWinningPosition = true;
    }

    public boolean isWinningState() {
        return isWinningPosition;
    }

    @Override
    public String toString() {
        return "(" + row + ", " + col + "): " + dir.name();
    }

    @Override
    public State clone() {
        try {
            return (State)super.clone();
        } catch (CloneNotSupportedException e) {
            return null;
        }
    }
}
