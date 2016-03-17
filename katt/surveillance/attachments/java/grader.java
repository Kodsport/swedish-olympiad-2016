import java.io.*;
import java.util.*;

public class grader {

	public static void main(String... args) throws IOException {
		BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter w = new PrintWriter(new BufferedOutputStream(System.out));
    String[] bw = r.readLine().split(" ");
    int B = Integer.parseInt(bw[0]),
        W = Integer.parseInt(bw[1]);

    int[][] S = new int[B][B];
    for (int i = 0; i < B; ++i) {
      String[] s = r.readLine().split(" ");
      for (int j = 0; j < B; ++j) S[i][j] = Integer.parseInt(s[j]);
    }
    int[][] T = new int[W][W];
    for (int i = 0; i < W; ++i) {
      String[] t = r.readLine().split(" ");
      for (int j = 0; j < W; ++j) T[i][j] = Integer.parseInt(t[j]);
    }

    w.println(surveillance.surveillance(B, W, S, T));
		w.close();
	}

}
