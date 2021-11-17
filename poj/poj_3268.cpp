// POJ 3268 Silver Cow Party
/*
	思路：
	正向最短路 + 反向最短路 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

struct Node {
	int to, cost;
	Node(int t_, int c_) {
		to = t_;
		cost = c_;
	}
	bool operator < (Node n1) const {
		return cost > n1.cost;
	}
};

const int INF = 0x3f3f3f3f;
const int maxn = 1010;

int n, m, x;
vector<Node> graph1[maxn];
vector<Node> graph2[maxn];
int dist1[maxn];
int dist2[maxn];
bool vis[maxn];

void Dijkstra1(int s) {
	priority_queue<Node> que;
	memset(dist1, INF, sizeof(dist1));
	memset(vis, false, sizeof(vis));

	dist1[s] = 0;
	que.push(Node(s, 0));
	while(!que.empty()) {
		Node n1 = que.top(); que.pop();
		int u = n1.to;

		if(vis[u]) continue;
		vis[u] = true;

		for(int i = 0; i < graph1[u].size(); i++) {
			Node e = graph1[u][i];
			if(dist1[e.to] > dist1[u]+e.cost) {
				dist1[e.to] = dist1[u]+e.cost;
				que.push(Node(e.to, dist1[e.to]));
			}
		}
	}
}

void Dijkstra2(int s) {
	priority_queue<Node> que;
	memset(dist2, INF, sizeof(dist2));
	memset(vis, false, sizeof(vis));

	dist2[s] = 0;
	que.push(Node(s, 0));
	while(!que.empty()) {
		Node n1 = que.top(); que.pop();
		int u = n1.to;

		if(vis[u]) continue;
		vis[u] = true;

		for(int i = 0; i < graph2[u].size(); i++) {
			Node e = graph2[u][i];
			if(dist2[e.to] > dist2[u]+e.cost) {
				dist2[e.to] = dist2[u]+e.cost;
				que.push(Node(e.to, dist2[e.to]));
			}
		}
	}
}

void solve() {
	Dijkstra1(x);
	Dijkstra2(x);
	
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		ans = max(ans, dist1[i]+dist2[i]);
	}
	
	cout << ans << endl;
}

int main() {
	cin >> n >> m >> x;

	int a, b, c;
	while(m--) {
		scanf("%d%d%d", &a, &b, &c);
		graph1[a].push_back(Node(b, c));
		graph2[b].push_back(Node(a, c));
	}
	solve();

	return 0;
}
