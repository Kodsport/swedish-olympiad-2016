import java.io.*;
import java.util.*;

public class grader {

	public static void main(String... args) throws IOException {
		BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter w = new PrintWriter(new BufferedOutputStream(System.out));
    int N = Integer.parseInt(r.readLine());
    char[] X = r.readLine().toCharArray();
    w.println(fibonacci.fibonacci(N, X));
		w.close();
	}

}
