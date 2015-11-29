package parser;

import java.io.*;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class Runner {
    // Parameters: context (contains the Grid and an initial State), and a Reader, for reading the program
    public static List<State> run(Context context, Reader reader) throws IOException, Lexer.InvalidTokenException, ParseException {
        Parser parser = new Parser(new Lexer(reader));
        ParseTree root = parser.Program(); // Construct the parse tree.
        List<Step> stepList = new ArrayList<>();
        root.evaluate(stepList); // Convert the parse tree to a sequence (List) of Steps.

        // List to contain the history of all states.
        List<State> stateList = new ArrayList<>();
        stateList.add(context.state);

        int pos = 0;
        Stack<StackFrame> stack = new Stack<StackFrame>();
        stack.push(new StackFrame());
        while(pos < stepList.size()) {
            Step step = stepList.get(pos);
            System.out.println("executing step " + step.getClass().getSimpleName());
            step.execute(context, stack);
            pos = step.getNextInstruction(stack, pos);
            System.out.println(context.state);
            stateList.add(context.state);

            if(context.grid.getGrid()[context.state.getRow()][context.state.getCol()] == Grid.SquareType.GOAL) {
                System.out.println("Yay, you won!");
                return stateList;
            }
        }

        return stateList;
    }


    public static void main(String[] args) throws IOException, Lexer.InvalidTokenException, ParseException {
        Context context = Context.readInitialConfig(new FileInputStream(new File(args[0])));
        run(context, new InputStreamReader(System.in));
    }
}
