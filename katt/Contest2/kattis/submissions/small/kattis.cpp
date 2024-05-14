#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define all(x) x.begin(), x.end()
#define trav(it, x) for (auto it = x.begin(); it != x.end(); ++it)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Event {

	int interval;
	double pos;
	bool type;

	Event(int interval, double pos, bool type) : 
		interval(interval),
		pos(pos),
		type(type)
	{}

	bool operator<(const Event& other) const {
		if(pos != other.pos) return pos < other.pos;;
		if(type != other.type) return !type;
		if(interval != other.interval) return interval < other.interval;
		return false;
	}

};

int kattis(int N, int H, int X_[], int Y_[], int Z_[]) {
	if (N > 1000) return 0;
	vector<pii> wall(N);
	vector<int> special(N);

	for(int i = 0; i < N; ++i) {
		wall[i].first = X_[i];
		wall[i].second = Y_[i];
		special[i] = Z_[i];
	}

	vector<pii> q;

	vector<Event> events;

	for(int K = 1; K >= 0; --K){

	for(int m = 0; m < N; ++m){
		int i = K ? m : (N - m - 1);
		double delta = K ? -1e-10 : 1e-10;
		double infin = K ? -1e50 : 1e50;
		const pii& p = wall[i];
		while(!q.empty()){
			const pii& p2 = q.back();
			if(p.second >= p2.second){
				q.pop_back();
				continue;
			} else if(q.size() >= 2){
				int dy1 = p.second - q[q.size() - 1].second;
				int dy2 = p.second - q[q.size() - 2].second;

				int dx1 = p.first - q[q.size() - 1].first;
				int dx2 = p.first - q[q.size() - 2].first;

				if( (dy1 * dx2 > dy2 * dx1) == K){
					q.pop_back();
				} else {
					break;
				}

			} else break;
		}
		if(special[i]){
			if(!q.empty()){
				const pii& p2 = q.back();
//cout << "Considering "<< p.first << " " << p.second << endl;
//cout << "Blocker: " << p2.first << " " << p2.second << endl;
				double k = (p2.second - p.second + .0) / (p.first - p2.first);
				double move = (H - p.second) / k;
				double canSee = p.first - move;
				events.push_back(Event(i, canSee + delta, K));
			} else {
				events.push_back(Event(i, infin, K));
			}
		}
		q.push_back(p);
	}

	q.clear();

	}

	sort(all(events));

/*	trav(it, events){
		cout << it->pos << " " << it->interval << " " << it->type << endl;
	}
	*/

	vector<int> ign;
	set<int> ign2;
	int ans = 0;

	trav(it, events){
		const Event& e = *it;
		if(e.type == true){
// left endpoint
			ign.push_back(e.interval);
		} else {
// right endpoint
			if(ign2.count(e.interval)) continue;
			ans++;	
			ign2.insert(all(ign));
			ign.clear();
		}
	}

	return ans;

}
