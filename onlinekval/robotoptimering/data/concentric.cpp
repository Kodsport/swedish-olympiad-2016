#include<bits/stdc++.h>

using namespace std;

int main() {
	srand(time(NULL));
	int R = 201, C = 201;
	vector<vector<char>> g(R, vector<char>(C, '.'));
	g[100][100] = 'M';
	g[0][0] = 'S';
	for(int i = 0;; ++i){
		int rs = 99 - 3*i;
		int cs = 100;
		if(rs < 0) break;

		int len =  1 + 3*i;

		int rem = rand()%(4 * len);

		for(int j = 0; j < len; ++j) {
			if(rem--)
			g[rs][cs] = '#';
			rs++;
			cs++;
		}
		for(int j = 0; j < len; ++j) {
			if(rem--)
			g[rs][cs] = '#';
			rs++;
			cs--;
		}
		for(int j = 0; j < len; ++j) {
			if(rem--)
			g[rs][cs] = '#';
			rs--;
			cs--;
		}
		for(int j = 0; j < len; ++j) {
			if(rem--)
			g[rs][cs] = '#';
			rs--;
			cs++;
		}
	}
	g[0][0] = '>';
	for(int i = 0; i < R; ++i){
		for(int j = 0; j < C; ++j){
			printf("%c", g[i][j]);
		}
		printf("\n");
	}
}
