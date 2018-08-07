import java.io.*;
import java.util.*;

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
		try {
			if(!Runner.runAndGetBooleanResult(context, code)) {
				throw new Exception("The robot did not reach the goal");
			}
			code = new StringReader(theCode);
			double score = getScore(code, bestLength);
			teamwriter.write("Case " + args[0] + ": score " + score + "\n");
			scorewriter.write(score + "\n");
		} catch(Exception e){
			e.printStackTrace();
			teamwriter.write("Case " + args[0] + ": " + e.toString() + "\n");
			scorewriter.write("0\n");
		} finally {
			teamwriter.close();
			scorewriter.close();
		}
		System.exit(42);
	}

	public static double getScore(Reader code, int bestLength) throws Exception {
		Lexer lexer = new Lexer(code);

		Token token;
		double length = 0;
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
		double score = (length - bestLength) / length;
		if(score < 0) score = 0;
		return 10 * (1 - Math.pow(score, 2));
	}

}
