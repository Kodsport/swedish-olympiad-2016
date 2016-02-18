import java.io.*;

public class grader {

    public static void main(String... args) throws IOException {
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter w = new PrintWriter(new BufferedOutputStream(System.out));
        int N = Integer.parseInt(r.readLine());

        int[] L = new int[N],
              H = new int[N],
              T = new int[N];

        String[] partsL = r.readLine().split(" "),
                 partsH = r.readLine().split(" "),
                 partsT = r.readLine().split(" ");

        for (int i = 0; i < N; ++i) {
            L[i] = Integer.parseInt(partsL[i]);
            H[i] = Integer.parseInt(partsH[i]);
            T[i] = Integer.parseInt(partsT[i]);
        }

        w.println(tshirts.tshirt(N, L, H, T));
        w.close();
    }

}
