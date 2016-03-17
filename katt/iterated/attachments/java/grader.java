import java.io.*;

public class grader {

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    int N = Integer.parseInt(in.readLine());
    String target = in.readLine();
    if (N != target.length()) {
      System.out.println("Invalid input string.");
      System.exit(2);
    }
    for (int i = 0; i < N; i++) {
      if (target.charAt(i) != '0' && target.charAt(i) != '1') {
        System.out.println("Invalid input string.");
        System.exit(2);
      }
    }

    lib.target = target;
    lib.N = N;
    iterated.init(N);
    System.out.println("Failure.");
    System.exit(1);
  }

  public static class lib {
    private static String target;
    private static int N, guesses;
    public static int guess(boolean[] ans) {
      assert ans.length == N;
      guesses++;
      int ret = 0;
      for (int i = 0; i < N; i++) {
        char c = target.charAt(i), d = ans[i] ? '1' : '0';
        ret += (c == d ? 1 : 0);
      }
      if (ret == N) {
        System.out.println("Success, took " + guesses + " guesses.");
        System.exit(0);
      }
      return ret;
    }
  }
}
