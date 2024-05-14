public class videoclips {

  static int[] next;
  static int steps;

  public static void videos(int K, int M, int[] S) {
    next = S;
    steps = M;
    if (steps > 1000) System.exit(0);
  }

  public static int clip(int I) {
    for (int i = 0; i < steps - 1; ++i) I = next[I];
    return I;
  }
}
