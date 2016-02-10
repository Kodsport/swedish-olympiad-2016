class mastermind {
	public static void init(int N) {
		boolean[] ar = new boolean[N];
		grader.lib.guess(ar);
		ar[0] = ar[1] = ar[2] = true;
		grader.lib.guess(ar);
	}
}
