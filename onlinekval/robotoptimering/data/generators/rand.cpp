#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv){
	if(argc < 4){
		printf("Usage: rows cols density\n");
		exit(0);
	}
	srand(time(NULL));
	int R = atoi(argv[1]);
	int C = atoi(argv[2]);
	double dens = atof(argv[3]);

	int cover = R * C * dens;

	vector<vector<char>> grid(R, vector<char>(C, '#'));
	int r, c;
	for(int i = 0; i < cover; ++i){
		do {
			r = rand() % R;
			c = rand() % C;
		} while(grid[r][c] == '.');
		grid[r][c] = '.';
	}
	do {
		r = rand() % R;
		c = rand() % C;
	} while(grid[r][c] == '.');
	grid[r][c] = 'v';
	fprintf(stderr, "%d %d\n", r, c);
	do {
		r = rand() % R;
		c = rand() % C;
	} while(grid[r][c] == '.');
	fprintf(stderr, "%d %d\n", r, c);
	grid[r][c] = 'M';
	for(int i = 0; i < R; ++i){
		for(int j = 0; j < C; ++j){
			printf("%c", grid[i][j]);
		}
		printf("\n");
	}
}
