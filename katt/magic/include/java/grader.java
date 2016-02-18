import java.io.*;
import java.util.*;

public class grader {

	public static void main(String[] args) throws IOException {
		BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter w = new PrintWriter(new BufferedOutputStream(System.out));
		String[] nk = r.readLine().split(" ");
		String[] l1 = r.readLine().split(" ");
		String[] r1 = r.readLine().split(" ");
		int N = Integer.parseInt(nk[0]);
		int K = Integer.parseInt(nk[1]);
		int[] L = new int[N];
		int[] R = new int[N];
		for (int i = 0; i < N; i++) {
			L[i] = Integer.parseInt(l1[i]);
			R[i] = Integer.parseInt(r1[i]);
		}

		lib.out = new int[N];
		int res = magic.magic_score(N, K, L, R);
		if (lib.outcount != N) {
			System.out.println("fail, " + lib.outcount + " tricks");
		} else {
			System.out.println(res);
			for (int s : lib.out)
				System.out.print(s + " ");
			System.out.println();
		}
	}

	public static class lib {
		private static int[] out;
		private static int outcount = 0;
		public static int trick(int ans) {
			if (outcount < out.length)
				out[outcount] = ans;
			outcount++;
		}
	}
}
