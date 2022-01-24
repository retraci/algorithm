// 201809-4
/*
	思路:
	Bellman_Ford 解决差分约束

	node：
	如果是求 d[i] - d[j] 的最大值 就是求最短路
	如果是求 d[i] - d[j] 的最小值 就是求最长路
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
	int to, cost;
	Node(int t_, int c_) {
		to = t_, cost = c_;
	}
};

const int maxn = 310;
const int INF = 0x3f3f3f3f;

int n;
vector<Node> G[maxn];
vector<int> dist;

void Bellman_Ford() {
	dist = vector<int> (n+2, 0);

	// 一共有 n+1 个点
	for(int k = 0; k <= n; k++) {
		bool updated = false;
		for(int i = 0; i <= n; i++) {
			for(int j = 0; j < G[i].size(); j++) {
				Node &e = G[i][j];
				if(dist[e.to] < dist[i] + e.cost) {
					updated = true;
					dist[e.to] = dist[i] + e.cost;
				}
			}
		}
		if(!updated) break;
	}
}

void solve() {
	Bellman_Ford();
	for(int i = 1; i <= n; i++) {
		if(i == n) cout << dist[i]-dist[i-1] << endl;
		else cout << dist[i]-dist[i-1] << " ";
	}
}

int main() {
	cin >> n;

	int b;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &b);
		if(i == 1) {
			G[i-1].push_back(Node(i+1, 2*b));
			G[i+1].push_back(Node(i-1, -(2*b+1)));
		} else if(i == n) {
			G[i-2].push_back(Node(i, 2*b));
			G[i].push_back(Node(i-2, -(2*b+1)));
		} else {
			G[i-2].push_back(Node(i+1, 3*b));
			G[i+1].push_back(Node(i-2, -(3*b+2)));
		}
	}
	for(int i = 1; i <= n; i++) G[i-1].push_back(Node(i, 1));
	solve();

	return 0;
}
