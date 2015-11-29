package parser;

import java.util.ArrayList;
import java.util.List;

public abstract class ParseTree {
    public abstract void evaluate(List<Step> steps);
}

class MoveNode extends ParseTree {
    private int line;

    public MoveNode(int line) {
        this.line = line;
    }

    @Override
    public void evaluate(List<Step> steps) {
        steps.add(new MoveStep(line));
    }
}

class RotateNode extends ParseTree {
    int line;
    boolean clockwise;

    public RotateNode(boolean clockwise, int line) {
        this.line = line;
        this.clockwise = clockwise;
    }

    @Override
    public void evaluate(List<Step> steps) {
        steps.add(new RotateStep(clockwise, line));
    }
}

class ForNode extends ParseTree {
    private ListNode list;
    private int n;
    private int line;

    public ForNode(ListNode list, int n, int line) {
        this.list = list;
        this.n = n;
        this.line = line;
    }

    @Override
    public void evaluate(List<Step> steps) {
        int startpos = steps.size();
        steps.add(new ForStartStep(n, line));
        list.evaluate(steps);
        steps.add(new ForStopStep(startpos, line));
    }
}

class ListNode extends ParseTree {
    List<ParseTree> commands;

    public ListNode() {

        commands = new ArrayList<>();
    }

    public void addCommand(ParseTree cmd) {
        commands.add(cmd);
    }

    @Override
    public void evaluate(List<Step> steps) {
        for(ParseTree cmd : commands) {
            cmd.evaluate(steps);
        }
    }
}
