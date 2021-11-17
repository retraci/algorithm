// POJ 2387 Til the Cows Come Home
/*
	思路：
	单源最短路（无负权 Dijkstra 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct Edge {
	int to, cost;
	Edge(int t_, int c_) {
		to = t_; cost = c_;
	}
	bool operator < (Edge e1) const {
		return cost > e1.cost;
	}
};

const int maxn = 1010;
const int INF = 0x3f3f3f3f;

int n, m;
vector<Edge> G[maxn];
int dist[maxn];
bool vis[maxn];

void Dijkstra(int s) {
	memset(vis, false, sizeof(vis));
	memset(dist, INF, sizeof(dist));
	
	priority_queue<Edge> que;
	dist[1] = 0;
	que.push(Edge(s, 0));
	while(!que.empty()) {
		Edge e1 = que.top(); que.pop();
		int u = e1.to;
		
		if(vis[u]) continue;
		
		vis[u] = true;
		for(int i = 0; i < G[u].size(); i++) {
			Edge e2 = G[u][i];
			if(dist[u]+e2.cost < dist[e2.to]) {
				dist[e2.to] = dist[u]+e2.cost;
				que.push(Edge(e2.to, dist[e2.to]));
			}
		}
	}
}

void solve() {
	Dijkstra(1);
	cout << dist[n] << endl;
}

int main() {
	cin >> m >> n;
	
	int a, b, c;
	for(int i = 0; i < m; i++) {
		scanf("%d%d%d", &a, &b, &c);
		G[a].push_back(Edge(b, c));
		G[b].push_back(Edge(a, c));
	}
	solve();
	
	return 0;
}
