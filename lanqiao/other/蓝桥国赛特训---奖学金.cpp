// 蓝桥国赛特训---奖学金
/*
	思路：
	点权换边权 + 最大费用流 
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 60*60*2+10;

struct Edge {
	int to, next, w, cost;
	Edge(int t_, int n_, int w_, int c_) {
		to = t_, next = n_, w = w_, cost = c_;
	}
};

int n, m, tot;
int s, t;
vector<Edge> es;
int head[maxn];
int dist[maxn];
int inQueue[maxn];
int pre[maxn];
int incf[maxn];
int maxFlow, ans;

void add_edge(int u, int v, int w, int c) {
	es.push_back(Edge(v, head[u], w, c)); head[u] = es.size()-1;
	es.push_back(Edge(u, head[v], 0, -c)); head[v] = es.size()-1;
}

bool spfa() {
	memset(dist, -1, sizeof(dist));
	memset(inQueue, 0, sizeof(inQueue));
	queue<int> que;
	que.push(s); inQueue[s] = 1;
	dist[s] = 0;
	incf[s] = INF;
	
	while (!que.empty()) {
		int u = que.front(); que.pop();
		inQueue[u] = 0;
		for (int i = head[u]; ~i; i=es[i].next) {
			int v = es[i].to;
			if (es[i].w && dist[v] < dist[u]+es[i].cost) {
				dist[v] = dist[u]+es[i].cost;
				pre[v] = i;
				incf[v] = min(es[i].w, incf[u]);
				if (!inQueue[v]) {
					que.push(v);
					inQueue[v] = 1;
				}
			}
		}
	}
	
	if (dist[t] == -1) return 0;
	return 1;
}

void update() {
	int x = t;
	while (x != s) {
		int i = pre[x];
		es[i].w -= incf[t];
		es[i^1].w += incf[t];
		x = es[i^1].to;
	}
	
	maxFlow += incf[t];
	ans += incf[t] * dist[t];
}

int solve() {	
	while (spfa()) {
		update();
	}
	cout << ans << endl;
}

int get_idx(int i, int j) {
	return (i-1)*m+j;
}

int main() {
	cin >> n >> m;
	tot = n*m;
	s = tot*2+1; t = s+1;
	
	memset(head, -1, sizeof(head));
	int tmp;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &tmp);
			add_edge(get_idx(i, j), get_idx(i, j)+tot, 1, tmp);
			add_edge(get_idx(i, j), get_idx(i, j)+tot, INF, 0);
			if (i+1 <= n) add_edge(get_idx(i, j)+tot, get_idx(i+1, j), INF, 0);
			if (j+1 <= m) add_edge(get_idx(i, j)+tot, get_idx(i, j+1), INF, 0);
		}
	}
	add_edge(s, get_idx(1, 1), 3, 0);
	add_edge(get_idx(n, m)+tot, t, 3, 0);
	solve();
	
	return 0;
}
