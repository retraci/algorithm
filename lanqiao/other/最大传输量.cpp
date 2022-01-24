// 最大传输量
/*
	最大流问题

	思路：
	FF 算法
	1.用 bfs 计算出离 出发点 s 的距离，将图分层
	2.用 dfs 寻找增广路，同时要满足 level[to] > level[v]
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 1e5;

typedef struct edge {
	int to, cap, rev;	// rev 是对应 G[v] 的下标 
};

int n, m;
vector<edge> G[maxn];
int level[maxn];
int iter[maxn];

void add_edge(int from, int to, int cap) {
	G[from].push_back((edge) {to, cap, G[to].size()});
	G[to].push_back((edge) {from, 0, G[from].size()-1});
}

void bfs(int s) {
	memset(level, -1, sizeof(level));
	level[s] = 0;
	queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int v = q.front();
		q.pop();
		for(int i = 0; i < G[v].size(); i++) {
			edge &e = G[v][i];
			if(e.cap > 0 && level[e.to] < 0) {
				level[e.to] = level[v] + 1;
				q.push(e.to);
			}
		}
	}
}

int dfs(int v, int t, int f) {
	if(v == t) return f;
	for(int &i = iter[v]; i < G[v].size(); i++) {
		edge &e = G[v][i];
		if(e.cap > 0 && level[e.to] > level[v]) {
			int d = dfs(e.to, t, min(f, e.cap));
			if(d > 0) {
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}	
	}
	return 0;
}

void solve() {
	int ans = 0;
	while(1) {
		bfs(0);
		if(level[n-1] == -1) break;
		memset(iter, 0, sizeof(iter));
		int f;
		while((f = dfs(0, n-1, INF)) > 0) {
			ans += f;
		}
	}
	printf("%d\n", ans);
}

int main() {
	n = 5, m = 7;
	add_edge(0, 1, 10);
	add_edge(0, 2, 2);
	add_edge(1, 2, 6);
	add_edge(1, 3, 6);
	add_edge(2, 4, 5);
	add_edge(3, 2, 3);
	add_edge(3, 4, 8);
	solve();

	return 0;
}
