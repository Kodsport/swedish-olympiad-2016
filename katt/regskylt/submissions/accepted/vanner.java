import java.util.HashSet;

public class vanner {

  private static HashSet<Integer> pos = new HashSet<Integer>();
  private static int sc;

  public static void init(int N, int L, int[] P){
    for (int i = 0; i < N; ++i) jump(-100, P[i]);
  }

  private static boolean in(int A) {
    return pos.contains(A);
  }

  public static void jump(int A, int B) {
    if (in(A - 1) || in(A + 1)) sc--;
    if (in(A - 1) && !in(A - 2)) sc--;
    if (in(A + 1) && !in(A + 2)) sc--;
    pos.remove(A);

    if (in(B - 1) || in(B + 1)) sc++;
    if (in(B - 1) && !in(B - 2)) sc++;
    if (in(B + 1) && !in(B + 2)) sc++;
    pos.add(B);
  }

  public static int score() {
    return sc;
  }

}
