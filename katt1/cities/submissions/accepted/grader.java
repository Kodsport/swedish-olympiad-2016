import java.io.*;
import java.util.StringTokenizer;


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

class cities
{
	static final int maxn = 100_000;
	static final Edge[] g = new Edge[maxn];
	static final int[] size = new int[maxn];
	static final boolean[] removed = new boolean[maxn];

	public static long paths(final int N, final int K, final int[] F, final int[] T)
	{
		for(int i = 0; i<N-1; i++)
		{
			g[F[i]] = new Edge(T[i], g[F[i]]);
			g[T[i]] = new Edge(F[i], g[T[i]]);
		}
		return split(0, N, K);
	}

	// Takes a subtree and return the number of nodes in the subtree
	// at distance K from one another.
	// i = node at which the subtree is rooted.
	// n = size of subtree.
	// K = target distance.
	static long split(final int i, final int n, final int K)
	{
		// The distance is bounded by the number of nodes.
		if(n <= K) return 0;
		// Calculate the size of subtrees.
		dfs(i);
		// Find centroid [start]
		int j = i, prv = -1;
		loop:while(true)
		{
			for(Edge e = g[j]; e!=null; e=e.nxt)
				if(!removed[e.to] && e.to!=prv && size[e.to]*2>n)
				{
					prv = j;
					j = e.to;
					continue loop;
				}
			// Find centroid [end]

			// Remove the node from the tree, aka split.
			removed[j] = true;
			// cnt[dst] = number of nodes at distance dst from j.
			final long[] cnt = new long[n];
			cnt[0] = 1;  // There's one node at distance 0.
			long sum = K==0 ? 1 : 0; // Number of nodes at distance K in this subtree.
			// First count the paths passing through j.
			for(Edge e = g[j]; e!=null; e=e.nxt)
				if(!removed[e.to])
				{
					// Count the number of nodes in the subtree rooted at
					// e.to with distance K from an already processed node.
					sum += count(e.to, 1, cnt, j, K);
					// Update the cnt[] array.
					add(e.to, 1, cnt, j, K);
				}
			// Then recurse on all remaining subtrees.
			for(Edge e = g[j]; e!=null; e=e.nxt)
				if(!removed[e.to])
				{
					if(size[e.to]>size[j]) sum += split(e.to, n-size[j], K);
					else sum += split(e.to, size[e.to], K);
				}
			return sum;
		}
	}
	// i = root node.
	static int dfs(final int i)
	{
		size[i] = -1; // trick to avoid visiting a node twice.
		int cnt = 1;
		for(Edge e = g[i]; e!=null; e=e.nxt)
			if(!removed[e.to] && size[e.to]>=0)
				cnt += dfs(e.to);
		return size[i] = cnt;
	}
	// i = root node, dst = distance from centroid,
	// cnt[d] = number of nodes at distance d from centroid,
	// p = parent node, K = target distance
	static long count(final int i, final int dst, final long[] cnt, final int p, final int K)
	{
		if(dst>K) return 0;
		long sum = cnt[K-dst];
		for(Edge e = g[i]; e!=null; e=e.nxt)
			if(!removed[e.to] && e.to!=p)
				sum += count(e.to, dst+1, cnt, i, K);
		return sum;
	}
	// i = root node, dst = distance from centroid,
	// cnt[d] = number of nodes at distance d from centroid,
	// p = parent node, K = target distance
	static void add(final int i, final int dst, final long[] cnt, final int p, final int K)
	{
		if(dst>K) return;
		cnt[dst]++;
		for(Edge e = g[i]; e!=null; e=e.nxt)
			if(!removed[e.to] && e.to!=p)
				add(e.to, dst+1, cnt, i, K);
	}

	// Edge class because Java library classes suck.
	private static class Edge
	{
		final int to; final Edge nxt;
		Edge(final int t, final Edge n)
		{
			to = t; nxt = n;
		}
	}

	public static void main(String[] klein) throws Exception
	{
		final Kattio in = new Kattio(System.in);
		final int N = in.getInt(), K = in.getInt();
		final int[] F = new int[N-1], T = new int[N-1];
		for(int i = 0; i<N-1; i++) F[i] = in.getInt();
		for(int i = 0; i<N-1; i++) T[i] = in.getInt();
		System.out.println(paths(N, K, F, T));
	}

}

class Kattio extends PrintWriter {
    public Kattio(InputStream i) {
        super(new BufferedOutputStream(System.out));
        r = new BufferedReader(new InputStreamReader(i));
    }
    public Kattio(InputStream i, OutputStream o) {
        super(new BufferedOutputStream(o));
        r = new BufferedReader(new InputStreamReader(i));
    }

    public boolean hasMoreTokens() {
        return peekToken() != null;
    }

    public int getInt() {
        return Integer.parseInt(nextToken());
    }

    public double getDouble() {
        return Double.parseDouble(nextToken());
    }

    public long getLong() {
        return Long.parseLong(nextToken());
    }

    public String getWord() {
        return nextToken();
    }



    private BufferedReader r;
    private String line;
    private StringTokenizer st;
    private String token;

    private String peekToken() {
        if (token == null)
            try {
                while (st == null || !st.hasMoreTokens()) {
                    line = r.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
                }
                token = st.nextToken();
            } catch (IOException e) { }
        return token;
    }

    private String nextToken() {
        String ans = peekToken();
        token = null;
        return ans;
    }
}
