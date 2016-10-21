import java.io.*;

public class stub {

	public static void main(String[] args) throws IOException {
		BufferedReader r = new BufferedReader(new FileReader(args[0]));
		PrintWriter w = new PrintWriter(new FileWriter(args[1]));
		int N = Integer.parseInt(r.readLine());

		lib.in = r;
		lib.out = w;
		lib.N = N;
		iterated.init(N);
	}

	public static class lib {
		private static BufferedReader in;
		private static PrintWriter out;
		private static int N;
		public static int guess(boolean[] ans) {
			StringBuilder sb = new StringBuilder(N);
			assert ans.length == N;
			for (int i = 0; i < N; i++)
				sb.append(ans[i] ? '1' : '0');
			int ret = -1;
			try {
				out.println(sb);
				out.flush();
				ret = Integer.parseInt(in.readLine());
				if (ret == N)
					System.exit(0);
			} catch (IOException e) {
				System.exit(2);
			}
			return ret;
		}
	}
}
