// 201903-5
/*
	思路：
	反向 Dijkstra  
*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct Node {
	int to, cost;
	Node(int t_, int c_) {
		to = t_, cost = c_;
	}
	bool operator < (const Node &t) const {
		return cost > t.cost;
	}
};

const int maxk = 1e2+10;
const int maxn = 1e4+10;
const int INF = 0x3f3f3f3f;

int n, m, K;
vector<int> vertex;
vector<Node> G[maxn];
int dist[maxn][maxn];
int vis[maxn];
int temp[maxn];

bool cmp(const int &a, const int &b) {
	return a < b;
}

void Dijkstra(int idx) {
	memset(vis, 0, sizeof(vis));
	int s = vertex[idx];
	dist[idx][s] = 0;
	priority_queue<Node> que;
	que.push(Node(s, 0));
	
	while(!que.empty()) {
		Node n1 = que.top(); que.pop();
		int u = n1.to;
		if(vis[u]) continue;
		vis[u] = 1;
		
		for(int i = 0; i < G[u].size(); i++) {
			Node n2 = G[u][i];
			int v = n2.to;
			if(dist[idx][v] > dist[idx][u] + n2.cost) {
				dist[idx][v] = dist[idx][u] + n2.cost;
				que.push(Node(v, dist[idx][n2.to]));
			}
		}
	}
}

void solve() {
	memset(dist, INF, sizeof(dist));
	for(int i = 0; i < vertex.size(); i++) {
		Dijkstra(i);
	}
	
	ll ans, cnt;
	for(int i = 1; i <= n; i++) {
		for(int idx = 0; idx < vertex.size(); idx++) {
			temp[idx] = dist[idx][i];
		}
		sort(temp, temp+vertex.size(), cmp);
		
		ans = 0, cnt = 0;
		for(int j = 0; j < K; j++) {
			if(temp[j] == INF) continue;
			ans += temp[j];
		}
		printf("%I64d\n", ans);
	}
}

int main() {
	cin >> n >> m >> K;
	
	int tmp;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &tmp);
		if(tmp) vertex.push_back(i);
	}
	
	int a, b, c;
	while(m--) {
		scanf("%d%d%d", &a, &b, &c);
		G[a].push_back(Node(b, c));
		G[b].push_back(Node(a, c));
	}
	solve();
	
	return 0;
}
