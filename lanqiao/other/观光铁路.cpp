// 蓝桥杯 观光铁路
/*
	未解决 
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 25;

struct Node {
	int v, last, dist;
	double rate;
	Node(int a, int b, double c, int d) {
		v = a;
		last = b;
		rate = c;
		dist = d;
	}
};

int n, m;
vector<int> G[MAXN];

double bfs(int s) {
	double res = 0;
	queue<Node> que;
	
	for(int i = 0; i < G[s].size(); i++) {
		que.push(Node(G[s][i], s, 1.0/G[s].size(), 1));
	}

	while(!que.empty()) {
		Node node = que.front(); que.pop();
		int u = node.v;
		if(u == s) {
			cout << res << endl;
			res += node.rate * node.dist;
			continue;
		}

		for(int k = 0; k < G[u].size(); k++) {
			int v = G[u][k];
			if(v == node.last || G[u].size() == 1) continue;
			double nr = 1.0/(G[u].size()-1) * node.rate;
			que.push(Node(v, u, nr, node.dist+1));
		}
	}
	return res;
}

void solve() {
	double ans[MAXN];

	for(int i = 1; i <= n; i++) {
		ans[i] = bfs(i);
	}
	
	for(int i = 1; i <= n; i++) {
		printf("%llf\n", ans[i]);
	}
}

int main() {
	cin >> n >> m;

	int a, b;
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	solve();

	return 0;
}
