#include <bits/stdc++.h>

using namespace std;

bool reasonable_keysize(const vector<int>& nums, int keylen){
  vector<set<int>> has(keylen);
  for(int i = 0; i < (int)nums.size(); ++i){
    has[i%keylen].insert(nums[i]);
  }
  int total = 0;
  for(int i = 0; i < keylen; i++) total += (int)has[i].size();
  return keylen <= 2 || total / keylen < 40;
}

bool works(const vector<int>& nums, int offset, int key, int keylen) {
  vector<int> distribution(256);
  for(int i = offset; i < (int)nums.size(); i += keylen){
    distribution[nums[i] ^ key]++;
  }
  int total = 0;
  for(int i = 0; i < 256; ++i){
    if(!isspace(i) && !isprint(i) && distribution[i]) {
      //cout << "fail print: " << i << endl;
      return false;
    }
    total += distribution[i];
  }
  if (distribution[' '] < total/15) return false;
  if (distribution['|'] + distribution['~'] > 20) return false;
  if (distribution['F'] + distribution['f'] + distribution['i'] + distribution['s'] + distribution['k'] >= total * 0.5) return true;

  int upper = 0;
  for(int i = 'A'; i <= 'Z'; i++) upper += distribution[i];
  int lower = 0;
  for(int i = 'a'; i <= 'z'; i++) lower += distribution[i];
  int spaces = distribution[' '] + distribution['\n'];
  if (upper + lower + spaces < total*0.90){
    //cout << "fail az-space: " << upper + lower + spaces << " " << total*0.99 << endl;
    return false;
  }
  if (upper > lower / 5) {
    //cout << "fail upper/lower"  << upper << " " << lower << endl;
    return false;
  }
  //cout << "lower: " << lower << endl;
  //cout << "distribution: " << distribution['a'] << " " << distribution['i'] << " " << distribution['e'] << " " << distribution['o'] << endl;
  int misses = 0;
  if (distribution['a'] < lower / 26) misses++;
  if (distribution['e'] < lower / 26) misses++;
  if (distribution['i'] < lower / 26) misses++;
  if (distribution['t'] < lower / 26) misses++;
  if (distribution['o'] < lower / 26) misses++;
  return misses < 2;
}

vector<int> decrypt(const vector<int>& nums, const vector<int>& key){
  vector<int> res;
  for(int i = 0; i < (int)nums.size(); ++i){
    res.push_back(nums[i] ^ key[i%int(key.size())]);
  }
  return res;
}

void try_solve(const vector<int>& nums, int keylen){
  //cout << "try length " << keylen << endl;
  if(!reasonable_keysize(nums, keylen)) return;
  vector<vector<int>> reasonable(keylen);
  for(int i = 0; i < keylen; i++){
    //cout << "testing location " << i << endl;
    for(int j = 0; j < 255; ++j){
      if(works(nums, i, j, keylen)) {
        reasonable[i].push_back(j);
        //cout << j << " works fine" << endl;
      }
    }
    if(reasonable[i].empty()) {
      //cout << "none worked" << endl;
      return;
    }
    if((int)reasonable[i].size() > 1) {
      assert(false && "too many worked");
    }
  }
  vector<int> key(keylen);
  for(int i = 0; i < keylen; ++i) key[i] = reasonable[i].front();
  vector<int> txt = decrypt(nums, key);
  for(int i = 0; i < (int)txt.size(); ++i){
    cout << (char)txt[i];
  }
  exit(0);
}

int todec(char i){
  if(isdigit(i)) return i - '0';
  else if ('a' <= i && i <= 'f') return i - 'a' + 10;
  else assert(false && "invalid char");
}

int main() {
  string txt, tmp;
  while(cin >> tmp) txt += tmp;
  vector<int> nums;
  for(int i = 0; i < (int) txt.size(); i += 2) {
    int a = todec(txt[i])*16 + todec(txt[i + 1]);
    //cout << "push " << a << endl;
    nums.push_back(a);
  }
  for(int i = 1; i <= 10; ++i) try_solve(nums, i);
}
