public class State implements Cloneable {
    public enum Direction {
        RIGHT, DOWN, LEFT, UP
    }

    private Position pos;
    private Direction dir;
    private int line;
    private boolean isWinningPosition = false;

    public State(int row, int col, Direction dir) {
        this.pos = new Position(row, col);
        this.dir = dir;
        line = 0;
    }

    public int getRow() {
        return pos.row;
    }

    public int getCol() {
        return pos.col;
    }

    public Position getPos() {
        return pos;
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
                return Math.PI / 2;
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

    public void updatePos(Position pos, int line) {
        this.pos = pos;
        this.line = line;
    }

    public void updateLine(int line) {
        this.line = line;
    }

    public void setAsWinningState() {
        isWinningPosition = true;
    }

    public boolean isWinningState() {
        return isWinningPosition;
    }

    public Position nextPosition(Grid grid) {
        if (getDir() == State.Direction.DOWN) {
            if(getRow()+1 < grid.getR() &&
                    grid.getGrid()[getRow() + 1][getCol()] != Grid.SquareType.BLOCKED) {
                return new Position(getRow() + 1, getCol());
            } else {
                return pos;
            }
        } else if (getDir() == State.Direction.UP) {
            if(getRow()-1 >= 0 &&
                    grid.getGrid()[getRow() - 1][getCol()] != Grid.SquareType.BLOCKED) {
                return new Position(getRow() - 1, getCol());
            } else {
                return pos;
            }
        } else if (getDir() == State.Direction.RIGHT) {
            if(getCol()+1 < grid.getC() &&
                    grid.getGrid()[getRow()][getCol()+1] != Grid.SquareType.BLOCKED) {
                return new Position(getRow(), getCol()+1);
            } else {
                return pos;
            }
        } else if (getDir() == State.Direction.LEFT) {
            if(getCol()-1 >= 0 &&
                    grid.getGrid()[getRow()][getCol()-1] != Grid.SquareType.BLOCKED) {
                return new Position(getRow(), getCol()-1);
            } else {
                return pos;
            }
        } else {
            return pos;
        }
    }

    @Override
    public String toString() {
        return "(" + pos.row + ", " + pos.col + "): " + dir.name();
    }

    @Override
    public State clone() {
        try {
            return (State)super.clone();
        } catch (CloneNotSupportedException e) {
            return null;
        }
    }

    class Position {
        int row, col;
        public Position(int row, int col) {
            this.row = row;
            this.col = col;
        }

        @Override
        public boolean equals(Object o) {
            if(!(o instanceof Position)) {
                return false;
            }
            Position p = (Position)o;
            return row == p.row && col == p.col;
        }
    }
}
