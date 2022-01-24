// 指派问题 
/*
	n 台电脑， k 个任务 
	
	思路： 
	二分图匹配问题
	可以转化成最大流问题
	加点 s，与点t 
*/ 

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std; 

typedef struct edge {
	int to, cap, rev;
};

const int INF = 0x3f3f3f3f;
const int maxn = 1e5;

int m;
int n, k;
vector<edge> G[maxn];
int level[maxn];
int iter[maxn];

void add_edge(int from, int to, int cap) {
	G[from].push_back((edge) { to, cap, G[to].size() });
	G[to].push_back((edge) { from, 0, G[from].size()-1 });
}

void bfs(int s) {
	memset(level, -1, sizeof(level));
	level[s] = 0;
	queue<int> que;
	que.push(s);
	while(!que.empty()) {
		int v = que.front(); que.pop();
		for(int i = 0; i < G[v].size(); i++) {
			edge &e = G[v][i];
			if(e.cap > 0 && level[e.to] == -1) {
				level[e.to] = level[v] + 1;
				que.push(e.to);
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
		if(level[m-1] == -1) break;
		memset(iter, 0, sizeof(iter));
		int f;
		while((f = dfs(0, m-1, INF)) > 0) {
			ans += f;
		}
	}
	
	printf("%d\n", ans);
}

int main() {
	n = 3, k = 3;
	m = n + k + 2;
	for(int i = 1; i <= n; i++) add_edge(0, i, 1);
	for(int i = n+1; i < m; i++) add_edge(i, m-1, 1);
	add_edge(1, n+1, 1); add_edge(1, n+2, 1);
	add_edge(2, n+1, 1); add_edge(2, n+3, 1);
	add_edge(3, n+2, 1);
	solve();
	
	return 0;
}
