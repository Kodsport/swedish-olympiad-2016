import java.util.*;

public class mafia {

  static long[] ways;

  public static void die(int N) {
    ways = new long[N + 1];
  }

  @SuppressWarnings("unchecked")
  public static void cops(int N, int M, int[] A, int[] B, int[] C) {
    List<Integer>[] adj1 = new List[N];
    List<Integer>[] adj2 = new List[N];
    for (int i = 0; i < N; ++i) {
      adj1[i] = new ArrayList<Integer>();
      adj2[i] = new ArrayList<Integer>();
    }
    for (int i = 0; i < M; ++i) {
      if (C[i] == 1) {
        adj1[A[i]].add(B[i]);
        adj1[B[i]].add(A[i]);
      } else {
        adj2[A[i]].add(B[i]);
        adj2[B[i]].add(A[i]);
      }
    }
    ways = new long[N + 1];
    int[] color = new int[N];
    ways[0] = 1;
    for (int i = 0; i < N; ++i) {
      if (color[i] == 0) {
        int blue = 0, red = 0;
        Queue<Integer> q = new LinkedList<Integer>();
        q.add(i);
        color[i] = 1;
        while (!q.isEmpty()) {
          int nx = q.poll();
          if (color[nx] == 1) blue++;
          else red++;
          for (int same : adj1[nx]) {
            if (color[same] == 0) {
              color[same] = color[nx];
              q.add(same);
            }
            if (color[nx] != color[same]) { die(N); return; };
          }
          for (int diff : adj2[nx]) {
            if (color[diff] == 0) {
              color[diff] = 3 - color[nx];
              q.add(diff);
            }
            if (color[nx] == color[diff]) { die(N); return; };
          }
        }
        long[] nways = new long[N + 1];
        for (int j = 0; j <= N; j++) {
          if (j + red <= N) nways[j + red] += ways[j];
          if (j + blue <= N) nways[j + blue] += ways[j];
        }
        ways = nways;
      }
    }
  }

  public static long guess(int C) {
    return ways[C];
  }
}
