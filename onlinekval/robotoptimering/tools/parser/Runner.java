package parser;

import java.io.*;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class Runner {
    public static List<State> run(Context context, Reader reader) throws IOException, InvalidTokenException, ParseException {
        Parser parser = new Parser(new Lexer(reader));
        ParseTree root = parser.Program();
        System.out.println("Parsing done");
        List<Step> stepList = new ArrayList<>();
        root.evaluate(stepList);
        System.out.println("Converted to steps");

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


    public static void main(String[] args) throws IOException, InvalidTokenException, ParseException {
        Context context = Context.readInitialConfig(new FileInputStream(new File(args[0])));
        run(context, new InputStreamReader(System.in));
    }
}
