import java.io.*;

public class cities
{
	static final int maxn = 100000;
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

}

