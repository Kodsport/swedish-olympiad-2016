#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

string rand_string(const int max_len) {
    const int len = (rand() % max_len) + 1;
    string s;
    for (int i = 0; i < len; ++i) {
        const char c = 'a' + (rand() % 26);
        s.push_back(c);
    }
    return s;
}

int main() {
    int seed;
    int size;
    int maxlen;
    cin >> seed >> size >> maxlen;
    srand(seed);
    vector<string> names;
    set<string> seen;
    const string myname = rand_string(maxlen);
    seen.insert(myname);
    cout << myname << endl;
    cout << size << endl;
    for (int i = 0; i < size-1; ++i) {
        for (;;) {
            const string attempt = rand_string(maxlen);
            if (seen.count(attempt) == 0) {
                seen.insert(attempt);
                cout << attempt << endl;
                break;
            }
        }
    }
    cout << myname << endl;
}
