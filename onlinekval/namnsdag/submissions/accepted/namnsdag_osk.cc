#include <iostream>
#include <vector>

using namespace std;

int main() {
    string name;
    cin >> name;
    int days;
    cin >> days;
    vector<string> names;
    for (int i = 0; i < days; ++i) {
        string cur;
        cin >> cur;
        if (cur.size() != name.size()) continue;
        int cnt = 0;
        for (int j = 0; j < cur.size(); ++j) {
            cnt += cur[j] != name[j];
        }
        if (cnt <= 1) {
            cout << i+1 << endl;
            return 0;
        }
    }
}
