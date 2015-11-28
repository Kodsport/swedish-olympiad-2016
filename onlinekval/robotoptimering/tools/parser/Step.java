package parser;

import java.util.Stack;

abstract class Step {
    int line;
    public Step(int line) {
        this.line = line;
    }

    public abstract void execute(Context context, Stack<StackFrame> stack, State state);
    public int getNextInstruction(Stack<StackFrame> stack, int current) {
        return current+1;
    }
}


class MoveStep extends Step {
    public MoveStep(int line) {
        super(line);
    }

    @Override
    public void execute(Context context, Stack<StackFrame> stack, State state) {
        if (state.getDir() == State.Direction.DOWN) {
            if(context.grid.getGrid()[state.getRow() + 1][state.getCol()] != Grid.SquareType.BLOCKED) {
                state.updatePos(state.getRow() + 1, state.getCol(), line);
            }
        } else if (state.getDir() == State.Direction.UP) {
            if(context.grid.getGrid()[state.getRow() - 1][state.getCol()] != Grid.SquareType.BLOCKED) {
                state.updatePos(state.getRow() - 1, state.getCol(), line);
            }
        } else if (state.getDir() == State.Direction.RIGHT) {
            if(context.grid.getGrid()[state.getRow()][state.getCol() + 1] != Grid.SquareType.BLOCKED) {
                state.updatePos(state.getRow(), state.getCol() + 1, line);
            }
        } else if (state.getDir() == State.Direction.LEFT) {
            if(context.grid.getGrid()[state.getRow()][state.getCol() - 1] != Grid.SquareType.BLOCKED) {
                state.updatePos(state.getRow(), state.getCol() - 1, line);
            }
        } else {
            throw new RuntimeException("Invalid direction on line " + line + ".");
        }
        return;
    }
}

class RotateStep extends Step {
    boolean clockwise;
    State.Direction[] dirs = {State.Direction.RIGHT, State.Direction.DOWN, State.Direction.LEFT, State.Direction.UP};

    private int dirToIndex(State.Direction d) {
        switch(d) {
            case RIGHT:
                return 0;
            case DOWN:
                return 1;
            case LEFT:
                return 2;
            case UP:
                return 3;
            default:
                throw new NullPointerException();
        }
    }

    public RotateStep(boolean clockwise, int line) {
        super(line);
        this.clockwise = clockwise;
    }

    @Override
    public void execute(Context context, Stack<StackFrame> stack, State state) {
        if(clockwise) {
            state.updateDir(dirs[( dirToIndex(state.getDir()) + 1 ) % 4], line);
        } else {
            state.updateDir(dirs[( dirToIndex(state.getDir()) + 3 ) % 4], line);
        }
    }
}

class ForStartStep extends Step {
    int n;

    public ForStartStep(int n, int line) {
        super(line);
        this.n = n;
    }

    @Override
    public void execute(Context context, Stack<StackFrame> stack, State state) {
        stack.peek().loopStack.push(n);
    }
}

class ForStopStep extends Step {
    int startpos;

    public ForStopStep(int startpos, int line) {
        super(line);
        this.startpos = startpos;
    }

    @Override
    public void execute(Context context, Stack<StackFrame> stack, State state) {
        stack.peek().loopStack.push(stack.peek().loopStack.pop() - 1);
    }

    @Override
    public int getNextInstruction(Stack<StackFrame> stack, int current) {
        if(stack.peek().loopStack.peek() > 0) {
            return startpos+1;
        } else {
            return current+1;
        }
    }
}

class StackFrame {
    Stack<Integer> loopStack;
}
