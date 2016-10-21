class iterated {
	public static void init(int N) {
		boolean[] g = new boolean[N];
		int cor = stub.lib.guess(g);
		for (int i = 0; i < N; i++) {
			g[i] = true;
			int cor2 = stub.lib.guess(g);
			if (cor2 < cor) g[i] = false;
			else cor = cor2;
		}
	}
}
