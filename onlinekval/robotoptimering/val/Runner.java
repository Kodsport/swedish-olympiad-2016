import java.io.*;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Stack;

public class Runner {
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
