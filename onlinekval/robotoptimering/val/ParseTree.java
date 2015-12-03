import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public abstract class ParseTree {
    public abstract void evaluate(List<Step> steps, Map<String, Integer> labels, List<Integer> forStack);
}

class MoveNode extends ParseTree {
    private int line;

    public MoveNode(int line) {
        this.line = line;
    }

    @Override
    public void evaluate(List<Step> steps, Map<String, Integer> labels, List<Integer> forStack) {
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
    public void evaluate(List<Step> steps, Map<String, Integer> labels, List<Integer> forStack) {
        steps.add(new RotateStep(clockwise, line));
    }
}

class ForNode extends ParseTree {
    private ListNode list;
    private int n;
    private int line;
    private int endline;

    public ForNode(ListNode list, int n, int line) {
        this.list = list;
        this.n = n;
        this.line = line;
        this.endline = list.endline;
    }

    @Override
    public void evaluate(List<Step> steps, Map<String, Integer> labels, List<Integer> forStack) {
        forStack.add(this.hashCode());

        int startpos = steps.size();
        steps.add(new ForStartStep(n, line));
        list.evaluate(steps, labels, forStack);
        steps.add(new ForStopStep(startpos, line, endline));

        forStack.remove(forStack.size()-1);
    }
}

class ListNode extends ParseTree {
    List<ParseTree> commands;
    int endline;

    public ListNode() {
        commands = new ArrayList<>();
    }

    public void addCommand(ParseTree cmd) {
        commands.add(cmd);
    }

    public void setEndline(int endline) {
        this.endline = endline;
    }

    @Override
    public void evaluate(List<Step> steps, Map<String, Integer> labels, List<Integer> forStack) {
        for(ParseTree cmd : commands) {
            cmd.evaluate(steps, labels, forStack);
        }
    }
}

class LabelNode extends ParseTree {
    String name;
    int line;

    public LabelNode(String name, int line) {
        this.name = name;
        this.line = line;
    }

    @Override
    public void evaluate(List<Step> steps, Map<String, Integer> labels, List<Integer> forStack) {
        List<Integer> stackCopy = new ArrayList<>(forStack);
        labels.put(name, steps.size());
        steps.add(new LabelStep(name, stackCopy, line));
    }
}

class GotoNode extends ParseTree {
    String label;
    boolean requireBlocked;
    int line;

    public GotoNode(String label, boolean requireBlocked, int line) {
        this.label = label;
        this.requireBlocked = requireBlocked;
        this.line = line;
    }

    @Override
    public void evaluate(List<Step> steps, Map<String, Integer> labels, List<Integer> forStack) {
        List<Integer> stackCopy = new ArrayList<>(forStack);
        steps.add(new GotoStep(label, requireBlocked, stackCopy, line));
    }
}

class CallNode extends ParseTree {
    String name;
    int line;

    public CallNode(String name, int line) {
        this.name = name;
        this.line = line;
    }

    @Override
    public void evaluate(List<Step> steps, Map<String, Integer> labels, List<Integer> forStack) {
        steps.add(new CallStep(name, line));
    }
}

class ReturnNode extends ParseTree {
    int line;

    public ReturnNode(int line) {
        this.line = line;
    }

    @Override
    public void evaluate(List<Step> steps, Map<String, Integer> labels, List<Integer> forStack) {
        steps.add(new ReturnStep(line));
    }
}
