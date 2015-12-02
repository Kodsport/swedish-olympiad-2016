public class Grid {
    public enum SquareType {
        EMPTY, BLOCKED, GOAL
    }

    private int R, C;
    private SquareType grid[][];

    public Grid(int R, int C, SquareType[][] grid) {
        this.R = R;
        this.C = C;
        this.grid = grid;
    }

    public SquareType[][] getGrid() {
        return grid;
    }

    public int getR() {
        return R;
    }

    public int getC() {
        return C;
    }
}
