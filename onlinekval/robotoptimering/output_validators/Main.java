import java.io.*;
import java.util.*;
import java.text.ParseException;

class Context {
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
class Grid {
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



class Lexer {
    private List<Token> tokens;
    int pos = 0;

    public Lexer(Reader r) throws IOException, InvalidTokenException {
        tokens = new ArrayList<>();
        BufferedReader br = new BufferedReader(r);

        int i = 1;
        String line = br.readLine();

        while(line != null) {
            String[] words = line.split("\\s");

            for(String t : words) {
                switch(t) {
                    case "":
                        continue;
                    case "forward":
                        tokens.add(new Token(TokenType.FWD, i));
                        break;
                    case "right":
                        tokens.add(new Token(TokenType.RIGHT, i));
                        break;
                    case "left":
                        tokens.add(new Token(TokenType.LEFT, i));
                        break;
                    case "for":
                        tokens.add(new Token(TokenType.FOR, i));
                        break;
                    case "{":
                        tokens.add(new Token(TokenType.LBRACE, i));
                        break;
                    case "}":
                        tokens.add(new Token(TokenType.RBRACE, i));
                        break;
                    case "call":
                        tokens.add(new Token(TokenType.CALL, i));
                        break;
                    case "return":
                        tokens.add(new Token(TokenType.RETURN, i));
                        break;
                    case "goto":
                        tokens.add(new Token(TokenType.GOTO, i));
                        break;
                    case "gotoblocked":
                        tokens.add(new Token(TokenType.GOTOBLOCKED, i));
                        break;
                    default:
                        if(t.matches("^[0-9]+$")) {
                            try {
                                tokens.add(new NumberToken(Integer.parseInt(t), i));
                            } catch(NumberFormatException e) {
                                throw new InvalidTokenException(t, i);
                            }
                        } else if(t.matches("^[a-z]+$")) {
                            tokens.add(new NameToken(t, i));
                        } else if(t.matches("^[a-z]+:$")) {
                            tokens.add(new LabelToken(t.substring(0, t.length()-1), i));
                        } else {
                            throw new InvalidTokenException(t, i);
                        }
                        break;
                }
            }

            line = br.readLine();
            i++;
        }
        tokens.add(new Token(TokenType.EOF, i));
    }

    public Token peekToken() {
        if(pos < tokens.size()) {
            return tokens.get(pos);
        } else {
            return null;
        }
    }

    public Token nextToken() {
        Token t = peekToken();
        pos++;
        return t;
    }

    public void print() {
        for(Token t : tokens) {
            System.out.println(t);
        }
    }

    public static class InvalidTokenException extends Exception {
        public InvalidTokenException(String token, int line) {
            super("Invalid token on line " + line + ": " + token);
        }
    }
}

public class Main {

	public static void main(String... args) throws IOException {
		// ./validator input judge_answer feedback_dir
		
		FileInputStream infile = new FileInputStream(args[0]);
		Scanner judge = new Scanner(new File(args[1]));
		int bestLength = judge.nextInt();

		Scanner s = new java.util.Scanner(System.in).useDelimiter("\\A");
		String theCode = "";
		try {
			theCode = s.next();
		} catch(Exception e) {
			// E.g. NoSuchElementException if no input
		}

		Reader code = new StringReader(theCode);

		Context context = Context.readInitialConfig(infile);
		if(!args[2].endsWith("/")) args[2] = args[2]+"/";
		File teamout = new File(args[2] + "teammessage.txt");
		File scorefile = new File(args[2] + "score.txt");
		BufferedWriter teamwriter = new BufferedWriter(new FileWriter(teamout));
		BufferedWriter scorewriter = new BufferedWriter(new FileWriter(scorefile));
		String[] parts = args[0].split("/");
		String casename = parts[parts.length - 1];
		try {
			if(!Runner.runAndGetBooleanResult(context, code)) {
				throw new Exception("The robot did not reach the goal");
			}
			code = new StringReader(theCode);
			int length = getLength(code);
			double score = getScore(length, bestLength);
			teamwriter.write("Case " + casename + ": score " + score + ". Best is " + bestLength + ", yours is " + length + "\n");
			scorewriter.write(score + "\n");
		} catch(Exception e){
			//e.printStackTrace();
			teamwriter.write("Case " + casename + ": " + e.toString() + "\n");
			scorewriter.write("0\n");
		} finally {
			teamwriter.close();
			scorewriter.close();
		}
		System.exit(42);
	}

	public static int getLength(Reader code) throws Exception {
		Lexer lexer = new Lexer(code);

		Token token;
		int length = 0;
		while( (token = lexer.nextToken()) != null ){
			switch(token.type) {
				case FWD:
				case RIGHT:
				case LEFT:
				case FOR:
				case CALL:
				case RETURN:
				case GOTOBLOCKED:
					length++;
				default:
			}
		}
		return length;
	}



	public static double getScore(int len, int bestLength) throws Exception {
		double length = len;
		double score = (length - bestLength) / length;
		if(score < 0) score = 0;
		return 10 * (1 - Math.pow(score, 2));
	}

}

class Parser {
    Lexer lexer;

    public Parser(Lexer lexer) {
        this.lexer = lexer;
    }

    public ParseTree Program() throws ParseException {
        ListNode node = new ListNode();
        while (lexer.peekToken().type != TokenType.EOF) {
            node.addCommand(Command());
        }
        return node;
    }

    public ListNode ForBlock() throws ParseException {
        ListNode node = new ListNode();

        Token next = lexer.nextToken();
        if (next.type != TokenType.LBRACE) {
            throw new ParseException("Expected { on line " + next.line + ", got " + next.toString() + ".", next.line);
        }

        while(true) {
            Token peeked = lexer.peekToken();

            if(peeked.type == TokenType.EOF) {
                throw new ParseException("Expected } on line " + peeked.line + ", got " + peeked.toString() + ".", peeked.line);
            } else if(peeked.type == TokenType.RBRACE) {
                Token end = lexer.nextToken();
                node.setEndline(end.line);
                break;
            }

            node.addCommand(Command());
        }

        return node;
    }

    public ParseTree Command() throws ParseException {
        Token next = lexer.nextToken();
        switch(next.type) {
            case FWD:
                return new MoveNode(next.line);
            case LEFT:
                return new RotateNode(false, next.line);
            case RIGHT:
                return new RotateNode(true, next.line);
            case FOR:
                Token number = lexer.nextToken();
                if (number.type != TokenType.NUMBER) {
                    throw new ParseException("Expected number on line " + number.line + ", got " + number.toString(), number.line);
                }
                int n = ((NumberToken)number).number;
                return new ForNode(ForBlock(), n, next.line);
            case LABEL:
                return new LabelNode(((LabelToken)next).name, next.line);
            case GOTO:
                Token name = lexer.nextToken();
                if(name.type != TokenType.NAME) {
                    throw new ParseException("Expected label name on line " + name.line + ", got " + name.toString(), name.line);
                }
                return new GotoNode(((NameToken)name).name, false, next.line);
            case GOTOBLOCKED:
                Token token = lexer.nextToken();
                if(token.type != TokenType.NAME) {
                    throw new ParseException("Expected label name on line " + token.line + ", got " + token.toString(), token.line);
                }
                return new GotoNode(((NameToken)token).name, true, next.line);
            case CALL:
                Token token2 = lexer.nextToken();
                if(token2.type != TokenType.NAME) {
                    throw new ParseException("Expected label name on line " + token2.line + ", got " + token2.toString(), token2.line);
                }
                return new CallNode(((NameToken)token2).name, next.line);
            case RETURN:
                return new ReturnNode(next.line);
            default:
                throw new ParseException("Unexpected token on line " + next.line + ": " + next.toString(), next.line);
        }
    }
}

abstract class ParseTree {
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

class Runner {
    public final static int MAX_STEPS = 100000000;

    /* Parameters:
        context: Context object, which contains the Grid and an initial State.
        reader: Reader for reading the program.
        stepsToSave: The number of states which should be returned (set to a reasonable value to avoid
            too high memory usage).
     */
    public static List<State> run(Context context, Reader reader, int stepsToSave) throws IOException, Lexer.InvalidTokenException, ParseException {
        Parser parser = new Parser(new Lexer(reader));
        ParseTree root = parser.Program(); // Construct the parse tree.
        List<Step> stepList = new ArrayList<>();
        context.steps = stepList;
        context.labels = new HashMap<>();
        root.evaluate(stepList, context.labels, new ArrayList<Integer>()); // Convert the parse tree to a sequence (List) of Steps.

		for (Step s : stepList) {
			s.init(context);
		}

        // List to contain the history of all states.
        List<State> stateList = new ArrayList<>();
        stateList.add(context.state);

        if(!context.labels.containsKey("main")) {
            throw new RuntimeException("Could not find 'main' label.");
        }

        int i = 0;
        int pos = context.labels.get("main");

        context.currentStep = pos;
        Stack<StackFrame> stack = new Stack<>();
        stack.push(new StackFrame());

        while(pos < stepList.size() && i < MAX_STEPS) {
            Step step = stepList.get(pos);
            pos = step.execute(context, stack);
            context.currentStep = pos;

            if(context.grid.getGrid()[context.state.getRow()][context.state.getCol()] == Grid.SquareType.GOAL) {
                context.state.setAsWinningState();
                stateList.add(context.state.clone());
                return stateList;
            }

            if(i < stepsToSave || pos >= stepList.size()) {
                stateList.add(context.state.clone());
            }

            i++;
        }

        if(i >= MAX_STEPS) {
            throw new RuntimeException("The robot was killed after " + i + " execution steps (100 million steps is the maximum allowed).");
        }

        return stateList;
    }

    public static boolean runAndGetBooleanResult(Context context, Reader reader) throws IOException, Lexer.InvalidTokenException, ParseException {
        List<State> states = run(context, reader, 0);
        return states.get(states.size()-1).isWinningState();
    }


    public static void main(String[] args) throws IOException, Lexer.InvalidTokenException, ParseException {
        Context context = Context.readInitialConfig(new FileInputStream(new File(args[0])));
        try {
            if(runAndGetBooleanResult(context, new InputStreamReader(System.in))) {
                System.out.println("Yay, you won!");
            } else {
                System.out.println("Sorry, the robot never reached its goal.");
            }
        } catch (Lexer.InvalidTokenException|ParseException|RuntimeException e) {
            System.out.println("" + e.getClass().getSimpleName() + ": " + e.getMessage());
        }
    }
}
class State implements Cloneable {
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

    static class Position {
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
enum TokenType {
    FWD, RIGHT, LEFT, FOR, CALL, RETURN, GOTO, GOTOBLOCKED, NUMBER, NAME, LABEL, LBRACE, RBRACE, EOF
}

class Token {
    TokenType type;
    final int line;

    public Token(TokenType type, int line) {
        this.type = type;
        this.line = line;
    }

    @Override
    public String toString() {
        return type.name();
    }
}

class NameToken extends Token {
    String name;

    public NameToken(String name, int line) {
        super(TokenType.NAME, line);
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }
}

class LabelToken extends NameToken {
    public LabelToken(String name, int line) {
        super(name, line);
        type = TokenType.LABEL;
    }
}

class NumberToken extends Token {
    int number;

    public NumberToken(int number, int line) {
        super(TokenType.NUMBER, line);
        this.number = number;
    }

    @Override
    public String toString() {
        return Integer.toString(number);
    }
}
