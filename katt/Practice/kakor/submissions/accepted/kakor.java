public class kakor {

  public static long cookies(int N, int[] A) {
    int ans = 0;
    for (int i = 0; i < N; ++i) ans += A[i];
    return ans;
  }

}
