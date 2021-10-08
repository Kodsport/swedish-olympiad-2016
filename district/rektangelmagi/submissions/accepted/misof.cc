// solution written by Michal 'misof' Forisek
#include<algorithm>
#include<iostream>
#include<sstream>
#include<vector>
using namespace std;

int R, C;
vector< vector<long long> > A; // equations

typedef pair<long long, long long> fraction;
fraction reduce(fraction x) {
	if (x.second < 0) { x.first *= -1; x.second *= -1; }
	long long d = __gcd(abs(x.first),abs(x.second));
	return fraction(x.first/d, x.second/d);
}
fraction operator+(fraction a, fraction b) { return reduce(fraction(a.first*b.second + b.first*a.second, a.second*b.second)); }
fraction operator-(fraction a, fraction b) { return reduce(fraction(a.first*b.second - b.first*a.second, a.second*b.second)); }
fraction operator*(long long a, fraction b) { return reduce(fraction(a*b.first, b.second)); }
fraction operator/(fraction a, long long b) { return reduce(fraction(a.first, a.second*b)); }

int main() {
	// read the input and construct the system of equations
	cin >> R >> C;
	for (int r=0; r<R; ++r) for (int c=0; c<C; ++c) {
		string S;
		cin >> S;
		if (S==".") continue;
		vector<long long> eqn(5);
		eqn[0] = 1-r-c+r*c;
		eqn[1] = r-r*c;
		eqn[2] = c-r*c;
		eqn[3] = r*c;
		stringstream(S) >> eqn[4];
		A.push_back(eqn);
	}

	// do the Gaussian elimination, adding equations if necessary
	for (int c=0; c<4; ++c) {
		for (int r=c; r<int(A.size()); ++r) if (A[r][c]!=0) {
			swap(A[c],A[r]);
			break;
		}
		if (c==int(A.size()) || A[c][c]==0) {
			vector<long long> eqn(5,0);
			eqn[c] = 1;
			A.push_back(eqn);
			swap(A[c],A[ A.size()-1 ]);
		}
		for (int r=c+1; r<int(A.size()); ++r) {
			long long d = __gcd( abs(A[r][c]), abs(A[c][c]) );
			long long m1 = A[r][c]/d, m2 = A[c][c]/d;
			for (int c2=0; c2<=4; ++c2) A[r][c2] = m1*A[c][c2] - m2*A[r][c2];
		}
	}

	// if we got a contradiction, report that there is no solution
	for (int r=4; r<int(A.size()); ++r) if (A[r][4]!=0) { cout << "ej magisk\n"; return 0; }

	// reconstruct the fractions from the triangular matrix
	fraction x4 = fraction(A[3][4], A[3][3]);
	fraction x3 = ( fraction(A[2][4],1) - A[2][3]*x4 ) / A[2][2];
	fraction x2 = ( fraction(A[1][4],1) - A[1][3]*x4 - A[1][2]*x3 ) / A[1][1];
	fraction x1 = ( fraction(A[0][4],1) - A[0][3]*x4 - A[0][2]*x3 - A[0][1]*x2 ) / A[0][0];
	for (int r=0; r<R; ++r) {
		for (int c=0; c<C; ++c) {
			if (c) cout << " ";
			fraction here = (1-r-c+r*c)*x1 + (r-r*c)*x2 + (c-r*c)*x3 + (r*c)*x4;
			cout << here.first;
			if (here.second>1) cout << "/" << here.second;
		}
		cout << endl;
	}
}
