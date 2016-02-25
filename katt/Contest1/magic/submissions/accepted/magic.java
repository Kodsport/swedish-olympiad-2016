import java.util.*;

class magic {
	public static int magic_score(int N, int K, int[] L, int[] R) {
		int[] ds = new int[N];
		for (int i = 0; i < N; i++) {
			assert R[i] - L[i] == 2;
			ds[i] = Math.min(Math.abs(L[i]), Math.abs(R[i]));
			grader.lib.trick(0);
		}
		Arrays.sort(ds);
		int res = 0;
		for (int x : ds) {
			if (x <= K) {
				K -= x;
				res++;
			}
		}
		return res;
	}
}
