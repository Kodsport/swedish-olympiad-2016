#include "validator.h"
#include <bits/stdc++.h>

void run() {
  int R = Int(1, Arg("R", 50));
  Space();
  int C = Int(1, Arg("C", 50));
  Endl();

  assert(R = Arg("r", R));
  assert(C = Arg("c", C));

  // These aren't used as of right now.
  bool isComplete = Arg("complete", "false") == "true";
  bool isUnique = Arg("unique", "false") == "true";
  bool isInts = Arg("ints", "false") == "true";

  // magic regex, don't question it
  regex allowed("(0|-?[1-9][0-9]*|\\.)");
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      string word = Word();
      assert(regex_match(word, allowed));
      if (c != C-1) { Space(); }
    }
    Endl();
  }
  Eof();
}