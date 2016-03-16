#include <stdlib.h>
#include <string.h>
// inwigilacja.cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<numeric>
#include<cmath>
using namespace std;

#define ALL(t) t.begin(),t.end()
#define FOR(i,n) for (int i=0; i<(int)(n); i++)
#define FOREACH(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++)
typedef vector<int> vi;
typedef long long int64;

typedef pair<int,int> p2;
int64 det(int x0,int y0,int x1,int y1) { return (int64)x0*y1-(int64)y0*x1; }
int64 dir(const p2 &a,const p2 &b,const p2 &c) { return det(a.first-b.first,a.second-b.second,c.first-b.first,c.second-b.second); }
#define MAX 110000
#define INF 1000100
struct ulamek {
  int64 p,q;
  ulamek(int64 _p=0,int64 _q=0) { p=_p; q=_q; }
  double round() { return (double)p/q; }
  bool operator<(const ulamek &x) const { return p*x.q<x.p*q; }
} left_bound[MAX],right_bound[MAX];
ostream &operator<<(ostream &out,ulamek u) { return out<<u.p<<"/"<<u.q; }

int kattis(int n, int h, int x[], int y[], int z[]) {
  FOR(i,n) scanf("%d %d %d",&x[i],&y[i],&z[i]);
//#define DRAW  
#ifdef DRAW  
  printf("\\documentclass[10pt,a4paper,oneside]{article}\n");
  printf("\\usepackage{tikz}\n");
  printf("\\begin{document}\n");
  printf("\\begin{center}\\begin{tikzpicture}[thick,scale=0.1]\n");
  printf("\\draw[dashed] (%d,%d) -- (%d,%d);\n",x[0],h,x[n-1],h);
  printf("\\fill[fill=black!40] (%d,%d)",x[0],y[0]);
  FOR(i,n-1) printf(" -- (%d,%d)",x[i+1],y[i+1]);
  printf(";\n");
  printf("\\draw (%d,%d)",x[0],y[0]);
  FOR(i,n-1) printf(" -- (%d,%d)",x[i+1],y[i+1]);
  printf(";\n");
  FOR(i,n) if (z[i]) printf("\\fill (%d,%d) circle(25pt);\n",x[i],y[i]);  
#endif  
  vector<p2> cur;
  FOR(i,n) {
    while (cur.size()>1 && dir(cur[cur.size()-2],cur.back(),p2(x[i],y[i]))<=0) cur.pop_back();
    cur.push_back(p2(x[i],y[i]));
    if (cur.size()==1 || cur[cur.size()-2].second<=cur.back().second)
      left_bound[i]=ulamek(0,1);
    else {
      int dx=cur.back().first-cur[cur.size()-2].first,dy=cur[cur.size()-2].second-cur.back().second;
      left_bound[i]=ulamek((int64)cur.back().first*dy-(int64)dx*(h-cur.back().second),dy);
    }
  }
  cur.clear();
  for (int i=n-1; i>=0; i--) {
    while (cur.size()>1 && dir(cur[cur.size()-2],cur.back(),p2(x[i],y[i]))>=0) cur.pop_back();
    cur.push_back(p2(x[i],y[i]));
    if (cur.size()==1 || cur[cur.size()-2].second<=cur.back().second)
      right_bound[i]=ulamek(x[n-1],1);
    else {
      int dx=cur[cur.size()-2].first-cur.back().first,dy=cur[cur.size()-2].second-cur.back().second;
      right_bound[i]=ulamek((int64)cur.back().first*dy+(int64)dx*(h-cur.back().second),dy);
    }
  }
  typedef pair<ulamek,ulamek> segment;
  typedef pair<segment,int> p2;
  vector<p2> t;
  FOR(i,n) if (z[i]) {
    if (ulamek(x[n-1],1)<right_bound[i]) right_bound[i]=ulamek(x[n-1],1);
    if (left_bound[i]<ulamek(x[0],1)) left_bound[i]=ulamek(x[0],1);
    t.push_back(p2(segment(right_bound[i],left_bound[i]),i));
  }
  sort(t.begin(),t.end());
  int taken=0;
  ulamek last(x[0]-1,1);
  FOR(i,t.size()) {
    if (last<t[i].first.second) {
      taken++;
      last=t[i].first.first;
#ifdef DRAW
      printf("\\fill[fill=red] (%.2lf,%d) circle(25pt);\n",last.round(),h);
#endif    
    }
#ifdef DRAW
    printf("\\draw[draw=red] (%d,%d) -- (%.2lf,%d);\n",x[t[i].second],y[t[i].second],last.round(),h);
#endif    
  }
#ifdef DRAW
  printf("\\end{tikzpicture}\\end{center}\n");
  printf("\\end{document}\n");  
#endif
  return taken;
}
