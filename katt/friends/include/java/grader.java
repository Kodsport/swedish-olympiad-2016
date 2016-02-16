import java.io.*;

public class grader {

  public static void main(String... args) throws IOException {
    BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter w = new PrintWriter(new BufferedOutputStream(System.out));
    String[] nlq = r.readLine().split(" ");
    int N = Integer.parseInt(nlq[0]),
        L = Integer.parseInt(nlq[1]),
        Q = Integer.parseInt(nlq[2]);
    String[] pStr = r.readLine().split(" ");
    int[] P = new int[N];
    for (int i = 0; i < N; ++i) {
      P[i] = Integer.parseInt(pStr[i]);
    }
    vanner.init(N, L, P);
    for (int i = 0; i < Q; ++i) {
      String[] q = r.readLine().split(" ");
      if (q[0].equals("1")) w.println(vanner.score());
      else {
        int A = Integer.parseInt(q[1]),
            B = Integer.parseInt(q[2]);
        vanner.jump(A, B);
      }
    }
    w.close();
  }

}
