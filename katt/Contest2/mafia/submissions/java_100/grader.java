import java.io.*;
import java.util.*;

public class grader {


  public static void main(String... args) throws IOException {
    BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter w = new PrintWriter(new BufferedOutputStream(System.out));
    String[] np = r.readLine().split(" ");
    int N = Integer.parseInt(np[0]),
        M = Integer.parseInt(np[1]);

    int[] A = new int[M];
    int[] B = new int[M];
    int[] T = new int[M];
    String[] partsA = r.readLine().split(" ");
    String[] partsB = r.readLine().split(" ");
    String[] partsT = r.readLine().split(" ");
    for (int i = 0; i < M; ++i) A[i] = Integer.parseInt(partsA[i]);
    for (int i = 0; i < M; ++i) B[i] = Integer.parseInt(partsB[i]);
    for (int i = 0; i < M; ++i) T[i] = Integer.parseInt(partsT[i]);

    int G = Integer.parseInt(r.readLine());
    String[] partsC = r.readLine().split(" ");
    int[] C = new int[G];
    for (int i = 0; i < G; ++i) C[i] = Integer.parseInt(partsC[i]);

    mafia.cops(N, M, A, B, T);
    for (int i = 0; i < G; ++i) {
      w.print(mafia.guess(C[i]));
      w.print(" ");
    }
    w.println();
    w.close();
  }

}
