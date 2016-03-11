import java.io.*;
import java.util.*;

public class grader {

	public static void main(String... args) throws IOException {
		BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter w = new PrintWriter(new BufferedOutputStream(System.out));
		String[] np = r.readLine().split(" ");
		int N = Integer.parseInt(np[0]),
			H = Integer.parseInt(np[1]);

		int[] X = new int[N],
			Y = new int[N],
			Z = new int[N];

		for (int i = 0; i < N; ++i) {
			String[] parts = r.readLine().split(" ");
			X[i] = Integer.parseInt(parts[0]);
			Y[i] = Integer.parseInt(parts[1]);
			Z[i] = Integer.parseInt(parts[2]);
		}
		w.println(kattis.kattis(N, H, X, Y, Z));
		w.close();
	}

}
