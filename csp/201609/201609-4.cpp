// 201609-4 交通规划
/*
	思路：
	变形 Dijkstra 
	每次维护 dist 的同时，维护 cost
	cost[i] 表示 连上 i 的花费 
	
	node:
	Dijkstra 的 cmp 要逆序 
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
	int to, dis;
	Node(int t_, int d_) {
		to = t_;
		dis = d_;
	}
	bool operator < (Node n1) const {
		return dis > n1.dis;
	}
};

const int INF = 0x3f3f3f3f;
const int maxn = 10010;

int n, m;
vector<Node> G[maxn];
int dist[maxn];
int cost[maxn];
int vis[maxn];

void Dijkstra(int s) {
	priority_queue<Node> que;
	memset(dist, INF, sizeof(dist));
	memset(cost, INF, sizeof(cost));
	memset(vis, 0, sizeof(vis));

	que.push(Node(s, 0));
	dist[s] = 0; cost[s] = 0;
	
	while(!que.empty()) {
		Node node = que.top(); que.pop();
		int u = node.to;
		
		if(vis[u]) continue;
		vis[u] = 1;
		
		for(int i = 0; i < G[u].size(); i++) {
			Node &e = G[u][i];
			if(dist[e.to] > dist[u]+e.dis) {
				dist[e.to] = dist[u]+e.dis;
				que.push(Node(e.to, dist[e.to]));
				cost[e.to] = e.dis;
			}
			if(dist[e.to]==dist[u]+e.dis && cost[e.to]>e.dis) {
				cost[e.to] = e.dis;
			}
		}
	}
}

void solve() {
	Dijkstra(1);

	int ans = 0;
	for(int i = 2; i <= n; i++) {
		ans += cost[i];
	}

	cout << ans << endl;
}

int main() {
	cin >> n >> m;

	int a, b, c;
	for(int i = 0; i < m; i++) {
		scanf("%d%d%d", &a, &b, &c);
		G[a].push_back(Node(b, c));
		G[b].push_back(Node(a, c));
	}
	solve();

	return 0;
}
