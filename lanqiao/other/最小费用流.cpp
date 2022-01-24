// 最小费用流
/*
	从 s 到 t 传输 F 大小的数据

	思路：
	最大流是通过 dfs 来边走边维护增广图的
	而最小费用流则需要用 单源最短路径来记录路径，之后再维护图
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

typedef struct edge {
	int to, cap, rev, cost;
};

const int INF = 0x3f3f3f3f;
const int maxn = 1e5;

int n, m, F;
vector<edge> G[maxn];
int dist[maxn];
int prev[maxn], prei[maxn];

void add_edge(int from, int to, int cap, int cost) {
	G[from].push_back((edge) {
		to, cap, G[to].size(), cost
	});
	G[to].push_back((edge) {
		from, 0, G[from].size()-1, cost
	});
}

void Bellman_Ford(int s) {
	memset(dist, INF, sizeof(dist));
	dist[s] = 0;
	bool update = true;
	for(int k = 0; k < n-1; k++) {
		update = false;
		for(int i = 0; i < n; i++) {
			if(dist[i] == INF) continue;
			for(int j = 0; j < G[i].size(); j++) {
				edge &e = G[i][j];
				if(e.cap > 0 && dist[e.to] > dist[i] + e.cost) {
					dist[e.to] = dist[i] + e.cost;
					prev[e.to] = i;
					prei[e.to] = j;
					update = true;
				}
			}
		}
	}

	update = false;
	for(int i = 0; i < n; i++) {
		if(dist[i] == INF) continue;
		for(int j = 0; j < G[i].size(); j++) {
			edge &e = G[i][j];
			if(e.cap > 0 && dist[e.to] > dist[i] + e.cost) {
				update = true;
			}
		}
	}
	
	if(update) {
		cout << -1 << endl;
		dist[n-1] = INF;
	}
}

void solve() {
	int ans = 0;

	while(F > 0) {
		Bellman_Ford(0);

		if(dist[n-1] == INF) {
			printf("-1\n");
			return;
		}
		int d = INF;
		for(int to = n-1; to != 0; to = prev[to]) {
			edge &e = G[prev[to]][prei[to]];
			d = min(d, e.cap);
		}
		F -= d;
		ans += d * dist[n-1];

		for(int to = n-1; to != 0; to = prev[to]) {
			edge &e = G[prev[to]][prei[to]];
			e.cap -= d;
			G[to][e.rev].cap += d;
		}
	}

	printf("%d\n", ans);
}

int main() {
	n = 5, m = 7, F = 9;
	add_edge(0, 1, 10, 2);
	add_edge(0, 2, 2, 4);
	add_edge(1, 2, 6, 6);
	add_edge(1, 3, 6, 2);
	add_edge(2, 4, 5, 2);
	add_edge(3, 2, 3, 3);
	add_edge(3, 4, 8, 6);
	solve();

	return 0;
}
