// 202009-1
/*

*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
	int dist, idx;
	Node(int d_, int i_) {
		dist = d_, idx = i_;
	}
	bool operator < (const Node &t) const {
		if (dist == t.dist) return idx < t.idx;
		return dist < t.dist;
	}
};

int n, x, y;
vector<Node> ds;

int get_dist(int a, int b) {
	return (x-a)*(x-a)+(y-b)*(y-b);
}

int main() {
	cin >> n >> x >> y;
	
	int a, b;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &a, &b);
		ds.push_back(Node(get_dist(a, b), i));
	}
	sort(ds.begin(), ds.end());
	for (int i = 0; i < 3; i++) {
		cout << ds[i].idx << endl;
	}
	
	return 0;
}
