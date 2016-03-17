// usage: ./a.out input_file correct_output output_dir < contestants_output

#include <bits/stdc++.h>
#include <poll.h>
#include <ext/stdio_filebuf.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define sz(x) (int)(x).size()

string type;
FILE* fd;

void die(const string& msg) {
  cout << 0 << endl;
  cerr << msg << endl;
  exit(0);
}

void accept(double score, int real_score) {
  cout << score << endl;
}

void safe_print(int n, ofstream& fout) {
  try {
    fout << n << endl;
  } catch(...) {
  }
}

string safe_read() {
  string guess;
  pollfd fifoInPollFD = {0, 0, 0};
  fifoInPollFD.fd = fileno(fd);
  fifoInPollFD.events = POLLIN;
  if(poll(&fifoInPollFD, 1, 1000) > 0) {
    string s;
    char ch;
    while ((ch = fgetc(fd)) > 0) {
      if (ch == '\n') break;
      s += ch;
    }
    return s;
  }
  throw 0;
}

int N;
double score(int guesses, int best) {
  if (type == "exp") {
    assert(N <= 30);
    return (guesses <= (1 << N));
  }
  if (type == "2n") return (guesses <= 2*N);
  if (type == "n") return (guesses <= 2+N);
  if (type == "rel") {
    if (guesses >= N) return 0;
    assert(guesses >= best);
    int a = N - guesses, b = N - best;
    return a / (double)b;
  }
  assert(false);
}

int main(int argc, char** argv) {
  try {
    cin.sync_with_stdio(0);
    cin.tie(0);
    int seed;
    cin >> N >> type >> seed;

    fd = fopen(argv[1], "rw");
    ofstream fout(argv[2], ofstream::out|ofstream::in);

    srand(seed);

    string guess, target(N, '0');
    rep(i,0,N) target[i] = (char)('0' + ((rand() >> 24) & 1));

    safe_print(N, fout);
    int guesses = 0;
    while (guess != target) {
      guesses++;
      try {
        cout << "reading new guess" << endl;
        guess = safe_read();
        cout << "read guess" << endl;
      } catch(...) {
        cout << "crash" << endl;
        die("no input!");
      }
      if (sz(guess) != N)
        die("wrong length");
      int s = 0;
      rep(i,0,N) {
        char x = guess[i];
        if (x != 48 && x != 49)
          die("invalid char in guess");
        if (x == target[i])
          s++;
      }
      safe_print(s, fout);
    }
    double sc = score(guesses, N / 2);
    if (sc == 0)
      die("too many guesses");
    accept(sc, guesses);
  } catch (...) {
    die("unknown error");
  }
}
