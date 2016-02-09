import java.io.*;

public class grader {

  public static void main(String... args) throws IOException {
    BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter w = new PrintWriter(new BufferedOutputStream(System.out));
    int N = Integer.parseInt(r.readLine());
    for (int i = 0; i < N; ++i) {
		String[] digits = r.readLine().split(" ");
		int[] P = new int[6];
		for(int j = 0; j < 6; ++j)
			P[j] = Integer.parseInt(digits[j]);
		w.println(regskylt.plate(P));
    }
  }

}
