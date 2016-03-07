import java.io.*;
import java.util.*;

public class grader {


	public static void main(String... args) throws IOException {
		BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter w = new PrintWriter(new BufferedOutputStream(System.out));
		String[] np = r.readLine().split(" ");
		int N = Integer.parseInt(np[0]),
				P = Integer.parseInt(np[1]);

		int[] C = new int[N],
			F = new int[N - 1],
			T = new int[N - 1];

		String[]
			partsC = r.readLine().split(" "),
						 partsF = r.readLine().split(" "),
						 partsT = r.readLine().split(" ");

		for (int i = 0; i < N; ++i) {
			C[i] = Integer.parseInt(partsC[i]);
		}
		for (int i = 0; i < N - 1; ++i) {
			F[i] = Integer.parseInt(partsF[i]);
			T[i] = Integer.parseInt(partsT[i]);
		}
		w.println(kingdom.division(N, P, C, F, T));
		for (int p : lib.R) {
			w.print(p);
			w.print(" ");
		}
		w.close();
	}

	public static class lib {

		private static int[] R;
		public static void parts(int[] R) {
			lib.R = R;
		}

	}

}
