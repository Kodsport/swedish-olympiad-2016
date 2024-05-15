#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < (1<<n); i++)
    {
        string g;
        for (int j = 0; j < n; i++)
        {
            if (i&(1<<j)) g += "0";
            else g += "1";
        }
        cout << g << endl;
        int resp;
        cin >> resp;
    }
}