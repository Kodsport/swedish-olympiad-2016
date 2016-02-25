import java.io.*;

public class grader {

    public static void main(String... args) throws IOException {
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter w = new PrintWriter(new BufferedOutputStream(System.out));
		String[] nk = r.readLine().split(" ");
        int N = Integer.parseInt(nk[0]),
			K = Integer.parseInt(nk[1]);

        int[] F = new int[N - 1],
              T = new int[N - 1];

        String[] partsF = r.readLine().split(" "),
                 partsT = r.readLine().split(" ");

        for (int i = 0; i < N - 1; ++i) {
            F[i] = Integer.parseInt(partsF[i]);
            T[i] = Integer.parseInt(partsT[i]);
        }

        w.println(cities.paths(N, K, F, T));
        w.close();
    }

}
