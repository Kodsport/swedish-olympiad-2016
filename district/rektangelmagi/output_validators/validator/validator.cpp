#include "validator.h"
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) // ignore
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef long double ld;

// TODO: what if num==0
struct Frac {
  ll num;
  ll den;
  Frac() : num(0), den(1) {}
  Frac(ll num) : num(num), den(1) {}
  Frac(ll x, ll y) {
    assert(y != 0);
    num = x;
    den = y;

    if (num == 0) {
      den = 1;
    } else {
      ll GCD = gcd(num, den);
      num /= GCD;
      den /= GCD;
    }
  }
  Frac operator+(Frac b) {
    return Frac(num * b.den + den * b.num, den * b.den);
  }
  Frac operator-(Frac b) {
    return Frac(num * b.den - den * b.num, den * b.den);
  }
  Frac operator*(Frac b) { return Frac(num * b.num, den * b.den); }
  bool operator==(Frac b) { return num == b.num && den == b.den; }
  bool operator!=(Frac b) { return !(Frac(num, den) == b); }
};

void checkMagic() {
  string judgeLine;
  streampos currJudgePos = judge_ans.tellg();
  string authLine;

  if (!getline(judge_ans, judgeLine)) {
    judge_error("expected more output");
  }
  if (judgeLine != "ej magisk") {
    judge_ans.seekg(currJudgePos);
    return;
  }
  if (!(getline(author_out, authLine))) {
    wrong_answer("expected more output");
  }
  if (judgeLine != authLine) {
    wrong_answer("failed to detect that there is no solution");
  }
  accept();
}

Frac toFrac(string frac) {
  if (frac.find("/-") != string::npos) {
    frac.replace(frac.find("/-"), 2, "/");
    if (frac[0] == '-') {
      frac.erase(0, 1);
    } else {
      frac.insert(0, "-");
    }
  }

  Frac reFrac;
  size_t pos = frac.find("/");
  if (pos == string::npos) {
    return Frac(stoll(frac));
  } else {
    return Frac(stoll(frac.substr(0, pos)), stoll(frac.substr(pos + 1)));
  }
}

bool isArithmetic(vector<Frac> &seq) {
  if (seq.size() <= 1) {
    return true;
  }
  Frac diff = seq[1] - seq[0];
  rep(i, 2, seq.size()) {
    if (seq[i] != (seq[0] + Frac(i, 1) * diff)) {
      return false;
    }
  }
  return true;
}

void checkArithmetic() {
  int R, C;
  if (!(judge_in >> R >> C))
    judge_error("expected more input data");

  vector<vector<string>> inputData(R);
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      string line;
      if (!(judge_in >> line))
        judge_error("expected more input data");
      inputData[r].push_back(line);
    }
  }

  vector<vector<string>> outputData(R);
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      string line;
      if (!(author_out >> line))
        wrong_answer("expected more output");
      outputData[r].push_back(line);
    }
    if (outputData[r].size() != C) {
      wrong_answer("incorrect number of tokens in a row");
    }
  }

  string trailing;
  if (author_out >> trailing) {
    wrong_answer("trailing output");
  }

  // magic regex, don't question it
  regex allowed("-?[0-9]{1,20}(/-?[0-9]{1,20})?$");
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      if (!regex_match(outputData[r][c], allowed))
        wrong_answer("some token is not a properly formatted fraction");
    }
  }

  vector<vector<Frac>> fOutputData(R, vector<Frac>(C));
  rep(r, 0, R) {
    rep(c, 0, C) {
      fOutputData[r][c] = toFrac(outputData[r][c]);

      if (inputData[r][c] != ".") {
        if (fOutputData[r][c] != toFrac(inputData[r][c])) {
          wrong_answer("one of the input values was modified");
        }
      }
    }
  }

  for (auto x : fOutputData) {
    if (!isArithmetic(x))
      wrong_answer("some row is not an arithmetic sequence");
  }

  rep(c, 0, C) {
    vector<Frac> col;
    for (auto x : fOutputData) {
      col.push_back(x[c]);
    }
    if (!isArithmetic(col))
      wrong_answer("some column is not an arithmetic sequence");
  }
  accept();
}

int main(int argc, char **argv) {
  init_io(argc, argv);

  checkMagic();
  checkArithmetic();
}
