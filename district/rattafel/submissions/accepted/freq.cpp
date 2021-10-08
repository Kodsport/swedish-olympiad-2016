#include <bits/stdc++.h>

using namespace std;

int main(){
  vector<pair<int, int>> o(128);
  for(int i = 0; i < 128; ++i) o[i].second = i;

  vector<vector<pair<int, int>>> occ(128, o);
  string s;
  getline(cin, s);
  if(s[0] == '#') s[0] = 'T';

  for(int i = 0; i < (int)s.size() - 1; ++i){
    if(s[i + 1] != '#') occ[s[i]][s[i+1]].first++;
  }
  for(int i = 0; i < 128; ++i){
    sort(occ[i].begin(), occ[i].end(), greater<pair<int,int>>());
  }
  for(int i = 1; i < (int)s.size(); ++i){
    if(s[i] == '#') {
      char repl = (char)occ[s[i-1]][0].second;
      if(!isprint(repl)) repl = ' ';
      s[i] = (char)occ[s[i - 1]][0].second;
    }
  }
  cout << s << endl;
}
