#include "validator.h"

void run() {
	int n = Int(1, Arg("maxn"));
	Endl();

	SpacedInts(n, 0, 30);
	
	Eof();
}
