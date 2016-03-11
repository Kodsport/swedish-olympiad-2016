public class videoclips {

  static int[][] jmp;
  static int[] nx;

  public static void videos(int K, int M, int[] S) {
    jmp = new int[32][100000];
    nx = new int[100000];
    for (int i = 0; i < K; i++) jmp[0][i] = S[i];
    for (int i = 1; i < 32; ++i) {
      for (int j = 0; j < K; ++j) {
        jmp[i][j] = jmp[i-1][jmp[i-1][j]];
      }
    }

    for (int j = 0; j < K; ++j) {
      int m = M - 1;
      nx[j] = j;
      for (int i = 0; i < 32; ++i) {
        if (m%2 == 1) {
          nx[j] = jmp[i][nx[j]];
        }
        m /= 2;
      }
    }
  }

  public static int clip(int I) {
    return nx[I];
  }
}
