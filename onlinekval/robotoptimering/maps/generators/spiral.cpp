#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
	int R, C;
	if (argc < 3) {
		printf("Usage: gen r c\n");
		exit(0);
	}
	R = atoi(argv[1]);
	C = atoi(argv[2]);
	vector<vector<char>> ans(R, vector<char>(C, '#'));	
	printf("%d %d\n", R, C);
	int r = 1, c = 1;
	ans[r][c] = 'v';
	for(int i = 0; i < R + C; ++i){
		while(r + 2 < R && ans[r + 2][c] == '#') {
			r++;
			ans[r][c] = '.';
		}
		while(c + 2 < C && ans[r][c + 2] == '#') {
			c++;
			ans[r][c] = '.';
		}
		while(r >= 2 && ans[r - 2][c] == '#') {
			r--;
			ans[r][c] = '.';
		}
		while(c >= 2 && ans[r][c - 2] == '#') {
			c--;
			ans[r][c] = '.';
		}
	}
	ans[r][c] = 'M';
	for(int i = 0; i < R; ++i){
		for(int j = 0; j < C; ++j){
			printf("%c", ans[i][j]);
		}
		printf("\n");
	}

}
