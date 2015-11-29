package parser;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public abstract class ParseTree {
    public abstract void evaluate(List<Step> steps, Map<String, Integer> labels);
}

class MoveNode extends ParseTree {
    private int line;

    public MoveNode(int line) {
        this.line = line;
    }

    @Override
    public void evaluate(List<Step> steps, Map<String, Integer> labels) {
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
    public void evaluate(List<Step> steps, Map<String, Integer> labels) {
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
    public void evaluate(List<Step> steps, Map<String, Integer> labels) {
        int startpos = steps.size();
        steps.add(new ForStartStep(n, line));
        list.evaluate(steps, labels);
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
    public void evaluate(List<Step> steps, Map<String, Integer> labels) {
        for(ParseTree cmd : commands) {
            cmd.evaluate(steps, labels);
        }
    }
}

class LabelNode extends ParseTree {
    String name;

    public LabelNode(String name) {
        this.name = name;
    }

    @Override
    public void evaluate(List<Step> steps, Map<String, Integer> labels) {
        labels.put(name, steps.size());
    }
}