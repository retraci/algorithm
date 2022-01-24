// 201703-4 地铁修建
/*
	思路：
	Dijkstra 变形 
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
	int to, cost;
	Node(int t_, int c_) {
		to = t_, cost = c_;
	}
	bool operator < (Node n1) const {
		return cost > n1.cost;
	}
};

const int INF = 0x3f3f3f3f;
const int maxn = 100010;

int n, m;
vector<Node> G[maxn];
int dist[maxn];
int vis[maxn];

void Dijkstra(int s) {
	memset(dist, INF, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	
	priority_queue<Node> que;
	dist[s] = 0; 
	que.push(Node(s, 0));
	
	while(!que.empty()) {
		Node n1 = que.top(); que.pop();
		int u = n1.to;
		
		if(vis[u]) continue;
		vis[u] = 1;
		
		for(int i = 0; i < G[u].size(); i++) {
			Node e = G[u][i];
			
			int temp = max(e.cost, dist[u]);
			if(dist[e.to] > temp) {
				dist[e.to] = temp;
				que.push(Node(e.to, dist[e.to]));
			}
		}
	}
}

void solve() {
	Dijkstra(1);
	
	cout << dist[n] << endl;
}

int main() {
	int a, b, c;
	while(cin >> n >> m) {
		for(int i = 0; i <= n; i++) G[i].clear();

		for(int i = 0; i < m; i++) {
			scanf("%d%d%d", &a, &b, &c);
			G[a].push_back(Node(b, c));
			G[b].push_back(Node(a, c));
		}
		solve();
	}
	
	return 0;
}
