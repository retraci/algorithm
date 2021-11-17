// POJ 3259 Wormholes
/*
	思路：
	Bellman_Ford 判负环 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

struct Edge {
	int from, to, cost;
	Edge(int f_, int t_, int c_) {
		from = f_;
		to = t_;
		cost = c_;
	}
};

const int INF = 0x3f3f3f3f;
const int maxn = 510;

int n, m, e, w;
vector<Edge> es;
int dist[maxn];

bool Bellman_ford(int s) {
	bool flag = false;
	memset(dist, INF, sizeof(dist));
	dist[s] = 0;

	for(int i = 1; i <= n; i++) {
		flag = false;
		for(int j = 0; j < m; j++) {
			int u = es[j].from;
			int to = es[j].to;
			int cost = es[j].cost;

			if(dist[to] > dist[u]+cost) {
				dist[to] = dist[u]+cost;
				flag = true;
			}
		}
		if(!flag) break;
		if(flag && i==n) return false;
	}
	return true;
}

void solve() {
	if(!Bellman_ford(0)) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}

int main() {
	int T;
	cin >> T;
	
	while(T--) {
		cin >> n >> e >> w;
		es.clear();
		
		int a, b, c;
		for(int i = 0; i < e; i++) {
			scanf("%d%d%d", &a, &b, &c);
			es.push_back(Edge(a, b, c));
			es.push_back(Edge(b, a, c));
		}
		for(int i = 0; i < w; i++) {
			scanf("%d%d%d", &a, &b, &c);
			es.push_back(Edge(a, b, -c));
		}
		m = e*2+w;
		solve();
	}

	return 0;
}
