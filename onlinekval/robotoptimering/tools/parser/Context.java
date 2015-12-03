package parser;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.List;
import java.util.Map;
import java.util.ArrayList;

public class Context {
    public Grid grid;
    public State state;
    public Map<String,Integer> labels;
    public List<Step> steps;
    public int currentStep;

    public Context(Grid grid, State initialState) {
        this.grid = grid;
        this.state = initialState;
    }

    private static boolean canReachGoal(State state, Grid.SquareType[][] grid) {
        int R = grid.length, C = grid[0].length;
        boolean[][] reachable = new boolean[R][C];
        ArrayList<State.Position> q = new ArrayList<State.Position>();
        q.add(state.getPos());
        int[] dx = {-1,1,0,0};
        int[] dy = {0,0,-1,1};
        while (!q.isEmpty()) {
            State.Position p = q.remove(q.size() - 1);
            if (reachable[p.row][p.col]) {
                continue;
            }
            reachable[p.row][p.col] = true;
            for (int d = 0; d < 4; d++) {
                State.Position p2 = new State.Position(p.row + dx[d], p.col + dy[d]);
                if (p2.col < 0 || p2.row < 0 || p2.row >= R || p2.col >= C) {
                    continue;
                }
                Grid.SquareType type = grid[p2.row][p2.col];
                if (type == Grid.SquareType.GOAL) {
                    return true;
                }
                if (type == Grid.SquareType.EMPTY) {
                    q.add(p2);
                }
            }
        }
        return false;
    }

    public static Context readInitialConfig(InputStream stream) throws IOException {
        int R, C;
        BufferedReader br = new BufferedReader(new InputStreamReader(stream));
		br.readLine();
        String line = br.readLine();
        String[] words = (line != null ? line : "").split(" ");
        if (words.length != 2) {
            throw new IOException("There should be two numbers on the first line.");
        }
        R = Integer.parseInt(words[0]);
        C = Integer.parseInt(words[1]);

        Grid.SquareType[][] grid = new Grid.SquareType[R][C];
        State initialState = null;
        for(int i=0; i<R; i++) {
            String row = br.readLine();
            if (row == null) {
                throw new IOException("There should be " + (R+1) + " lines of input.");
            }
            if (row.length() != C) {
                throw new IOException("There should be " + C + " characters on each line of the map.\nLine " + (i+2) + " has " + row.length() + " characters.");
            }

            for(int j=0;j<row.length();j++) {
                State.Direction dir = null;
                switch(row.charAt(j)) {
                    case '.':
                        grid[i][j] = Grid.SquareType.EMPTY;
                        continue;
                    case '#':
                        grid[i][j] = Grid.SquareType.BLOCKED;
                        continue;
                    case 'M':
                        grid[i][j] = Grid.SquareType.GOAL;
                        continue;
                    case '>':
                        dir = State.Direction.RIGHT;
                        break;
                    case 'v':
                        dir = State.Direction.DOWN;
                        break;
                    case '<':
                        dir = State.Direction.LEFT;
                        break;
                    case '^':
                        dir = State.Direction.UP;
                        break;
                }

                if (dir != null) {
                    // We found a starting space.
                    if(initialState == null) {
                        initialState = new State(i, j, dir);
                    } else {
                        throw new IOException("There may only be one start position.");
                    }
                } else {
                    throw new IOException("Invalid character '"+ row.charAt(j) + "'.");
                }
            }
        }

        if (br.readLine() != null) {
            throw new IOException("There should be " + (R+1) + " lines of input.");
        }

        if(initialState == null) {
            throw new IOException("Could not find a start position.");
        }

        if(!canReachGoal(initialState, grid)) {
            throw new IOException("Could not find a path from start to goal.");
        }

        return new Context(new Grid(R, C, grid), initialState);
    }
}
