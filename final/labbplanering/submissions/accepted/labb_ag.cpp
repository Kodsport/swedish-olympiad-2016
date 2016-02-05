#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

#define rep(i, a, b) for(int i=int(a); i < int(b); i++)
typedef long long ll;

using namespace std;

int main() {
	int N;
	scanf("%d", &N);

	// Each element is a pair of (queue of task lengths, start time of first task).
	vector< pair< queue<int>, int > > students(N);

	rep(i, 0, N) {
		int m;
		scanf("%d", &m);
		students[i].second = -1;
		rep(j, 0, m) {
			int a;
			scanf("%d", &a);
			students[i].first.push(a);
		}
	}

	sort(students.begin(), students.end());

	int time = 0;

	// Make students start waiting in order of increasing first task length.
	rep(i, 0, N) {
		if (students[i].first.size() > 1) {
			int a = students[i].first.front();
			students[i].first.pop();
			students[i].second = time;
			time += a;
		}
	}

	// When all students (with >1 task) are waiting, the order does not matter.
	rep(i, 0, N) {
		while (students[i].first.size() > 1) {
			time += students[i].first.front();
			students[i].first.pop();
		}
	}

	ll cost = 0;
	// Go through all students which only had one task.
	rep(i, 0, N) {
		if (students[i].second == -1) {
			time += students[i].first.front();
			cost += students[i].first.front();
			students[i].first.pop();
		}
	}

	// Go through students still waiting in order of decreasing task length.
	sort(students.begin(), students.end(), [](const pair<queue<int>, int> &a, const pair<queue<int>, int> &b) -> bool { return b < a; });
	rep(i, 0, N) {
		if (!students[i].first.empty()) {
			time += students[i].first.front();
			cost += time - students[i].second;
			students[i].first.pop();
		}
	}

	printf("%lld\n", cost);
}
