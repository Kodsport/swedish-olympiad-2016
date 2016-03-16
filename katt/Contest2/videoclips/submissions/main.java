import java.io.*;
import java.util.*;

public class main {


  public static void main(String... args) throws IOException {
    BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter w = new PrintWriter(new BufferedOutputStream(System.out));
    String[] np = r.readLine().split(" ");
    int K = Integer.parseInt(np[0]),
        M = Integer.parseInt(np[1]);

    int[] S = new int[K];
    String[] partsS = r.readLine().split(" ");
    for (int i = 0; i < K; ++i) {
      S[i] = Integer.parseInt(partsS[i]);
    }

    videoclips.videos(K, M, S);

    int N = Integer.parseInt(r.readLine());
    String[] partsI = r.readLine().split(" ");
    for (int i = 0; i < N; ++i) {
      w.print(videoclips.clip(Integer.parseInt(partsI[i])));
      w.print(" ");
    }
    w.println();
    w.close();
  }

}

class videoclips {

  static int[] next;
  static int steps;

  public static void videos(int K, int M, int[] S) {
    next = S;
    steps = M - 1;
    if (steps > 1000) System.exit(0);
  }

  public static int clip(int I) {
    for (int i = 0; i < steps; ++i) I = next[I];
    return I;
  }
}
