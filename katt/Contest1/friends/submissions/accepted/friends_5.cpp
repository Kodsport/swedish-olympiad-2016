#include "friends.h"
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;

set<pair<int,int>> blocks;
ll sum;

ll value(int l, int r) {
    ll w = r-l+1;
    return w*w;
}

void add(int pos) {
    auto x = blocks.upper_bound({pos,pos});
    auto y = x;
    y--;
    int l1 = y->first;
    int r1 = y->second;
    int l2 = x->first;
    int r2 = x->second;
    if (r1 == pos-1 && l2 == pos+1) {
        blocks.erase(y);
        blocks.erase(x);
        sum -= value(l1,r1);
        sum -= value(l2,r2);
        blocks.insert({l1,r2});
        sum += value(l1,r2);
    } else if (r1 == pos-1) {
        blocks.erase(y);
        sum -= value(l1,r1);
        blocks.insert({l1,r1+1});
        sum += value(l1,r1+1);
    } else if (l2 == pos+1) {
        blocks.erase(x);
        sum -= value(l2,r2);
        blocks.insert({l2-1,r2});
        sum += value(l2-1,r2);
    } else {
        blocks.insert({pos,pos});
        sum += value(pos,pos);
    }
}

void remove(int pos) {
    auto x = blocks.lower_bound({pos+1,0});
    x--;
    int l = x->first;
    int r = x->second;
    sum -= value(l,r);
    blocks.erase(x);
    if (l == r) return;
    if (l == pos) {
        blocks.insert({l+1,r});
        sum += value(l+1,r);
    } else if (r == pos) {
        blocks.insert({l,r-1});
        sum += value(l,r-1);
    } else {
        blocks.insert({l,pos-1});
        blocks.insert({pos+1,r});
        sum += value(l,pos-1);
        sum += value(pos+1,r);
    }
}

void init(int N, int L, int* P) {
    blocks.insert({-2,-2});
    blocks.insert({L+1,L+1});
    for (int i = 0; i < N; i++) add(P[i]);
}

void jump(int A, int B) {
    remove(A);
    add(B);
}

ll score() {
    return sum;
}
