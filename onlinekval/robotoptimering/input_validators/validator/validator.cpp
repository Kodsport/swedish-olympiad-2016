#include "validator.h"
#include <cstring>
#include <vector>

typedef long long ll;

void run() {
    Line();
    int r = Int(1, 1000);
    Space();
    int c = Int(1, 1000);
    Endl();

    int numgoals = 0;
    int numstart = 0;
    for (int i = 0; i < r; i++)
    {
        string row = Line();

        for (auto c : row)
        {
            if (c=='.') {}
            else if (c=='#') {}
            else if (c=='M') { numgoals++; }
            else if (c=='<') { numstart++; }
            else if (c=='>') { numstart++; }
            else if (c=='v') { numstart++; }
            else if (c=='^') { numstart++; }
            else assert(0);
        }
    }
    assert(numgoals == 1);
    assert(numstart == 1);

    Eof();
}
