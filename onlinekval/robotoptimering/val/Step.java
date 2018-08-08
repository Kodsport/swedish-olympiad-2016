import java.util.List;
import java.util.Stack;

abstract class Step {
    int line;
    public Step(int line) {
        this.line = line;
    }

    public void init(Context context) {}

    // execute executes the step and returns the index of the next step
    public abstract int execute(Context context, Stack<StackFrame> stack);
}


class MoveStep extends Step {
    public MoveStep(int line) {
        super(line);
    }

    @Override
    public int execute(Context context, Stack<StackFrame> stack) {
        context.state.updatePos(context.state.nextPosition(context.grid), line);
        return context.currentStep + 1;
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
    public int execute(Context context, Stack<StackFrame> stack) {
        State state = context.state;
        if(clockwise) {
            state.updateDir(dirs[( dirToIndex(state.getDir()) + 1 ) % 4], line);
        } else {
            state.updateDir(dirs[( dirToIndex(state.getDir()) + 3 ) % 4], line);
        }
        return context.currentStep + 1;
    }
}

class ForStartStep extends Step {
    int n;

    public ForStartStep(int n, int line) {
        super(line);
        this.n = n;
    }

    @Override
    public int execute(Context context, Stack<StackFrame> stack) {
        stack.peek().loopStack.push(n);
        context.state.updateLine(line);
        return context.currentStep + 1;
    }
}

class ForStopStep extends Step {
    int startpos;
    int startline;

    public ForStopStep(int startpos, int startline, int line) {
        super(line);
        this.startpos = startpos;
        this.startline = startline;
    }

    @Override
    public int execute(Context context, Stack<StackFrame> stack) {
        if(stack.empty()) {
            throw new RuntimeException("Unexpected } on line " + line + ".");
        }
        stack.peek().loopStack.push(stack.peek().loopStack.pop() - 1);

        if(stack.peek().loopStack.peek() > 0) {
            context.state.updateLine(startline);
            return startpos+1;
        } else {
            context.state.updateLine(line);
            stack.peek().loopStack.pop();
            return context.currentStep+1;
        }
    }

}

class LabelStep extends Step {
    String name;
    List<Integer> forStack;

    public LabelStep(String name, List<Integer> forStack, int line) {
        super(line);
        this.name = name;
        this.forStack = forStack;
    }

    @Override
    public int execute(Context context, Stack<StackFrame> stack) {
        context.state.updateLine(line);
        return context.currentStep + 1;
    }
}

class GotoStep extends Step {
    String label;
    boolean requireBlocked;
    List<Integer> forStack;
	int target, pops;

    // Returns the number of pops from the for stack required to jump from s1 to s2, or -1 if the jump is illegal.
    public static int compareForStacks(List<Integer> s1, List<Integer> s2) {
        for(int i=0; i<s2.size(); i++) {
            if(i >= s1.size()) {
                return -1;
            } else if(s1.get(i) != s2.get(i)) {
                return -1;
            }
        }
        return s1.size()-s2.size();
    }

    public GotoStep(String label, boolean requireBlocked, List<Integer> forStack, int line) {
        super(line);
        this.label = label;
        this.requireBlocked = requireBlocked;
        this.forStack = forStack;
    }

	@Override
	public void init(Context context) {
        if(!context.labels.containsKey(label)) {
            throw new RuntimeException("Line " + line + ": Could not find label '" + label + "'.");
        }
        int index = context.labels.get(label);
        LabelStep label = (LabelStep)context.steps.get(index);
        this.pops = GotoStep.compareForStacks(this.forStack, label.forStack);

        if(this.pops == -1) {
            throw new RuntimeException("Line " + line + ": Tried to jump into a for loop.");
        }

		this.target = index;
	}

    @Override
    public int execute(Context context, Stack<StackFrame> stack) {
        context.state.updateLine(line);

        if(requireBlocked && !context.state.getPos().equals(context.state.nextPosition(context.grid))) {
            return context.currentStep + 1;
        }

        for(int i=0; i<this.pops; i++) {
            stack.peek().loopStack.pop();
        }
        return this.target;
    }
}

class CallStep extends Step {
    String label;
	int target;

    public CallStep(String label, int line) {
        super(line);
        this.label = label;
    }

	@Override
	public void init(Context context) {
        if(!context.labels.containsKey(label)) {
            throw new RuntimeException("Line " + line + ": Could not find label '" + label + "'.");
        }
		this.target = context.labels.get(label);
	}

    @Override
    public int execute(Context context, Stack<StackFrame> stack) {
        context.state.updateLine(line);

        int index = this.target;
        LabelStep label = (LabelStep)context.steps.get(index);

        if(label.forStack.size() > 0) {
            throw new RuntimeException("Line " + line + ": Tried to jump into a for loop.");
        }

        stack.peek().nextStepIndex = context.currentStep + 1;
        stack.push(new StackFrame());

        return index;
    }
}

class ReturnStep extends Step {

    public ReturnStep(int line) {
        super(line);
    }

    @Override
    public int execute(Context context, Stack<StackFrame> stack) {
        context.state.updateLine(line);
        stack.pop();
        return stack.peek().nextStepIndex;
    }
}

class StackFrame {
    Stack<Integer> loopStack;
    int nextStepIndex = -1;

    public StackFrame() {
        loopStack = new Stack<>();
    }
}
