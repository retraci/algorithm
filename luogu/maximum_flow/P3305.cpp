// luogu P3305
/*
	思路：
	二分 + 最大流 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 110;
const double eps = 1e-5;
const int INF = 0x3f3f3f3f;

struct Edge {
	int to, next;
	double w;
	Edge(int t_, int n_, double w_) {
		to = t_, next = n_, w = w_;
	}
};

int n, m, p;
int s, t;
vector<Edge> es;
int head[maxn];
int level[maxn];
int iter[maxn];
vector<double> ww;

void add_edge(int u, int v, double w) {
	ww.push_back(w); ww.push_back(0);
	es.push_back(Edge(v, head[u], w)); head[u] = es.size()-1;
	es.push_back(Edge(u, head[v], 0)); head[v] = es.size()-1;
}

bool bfs() {
	memset(level, 0, sizeof(level));
	queue<int> que;
	que.push(s);
	level[s] = 1;
	
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (int i = head[u]; ~i; i=es[i].next) {
			int v = es[i].to;
			if (es[i].w && !level[v]) {
				level[v] = level[u]+1;
				que.push(v);
			}
		} 
	}
	return level[t];
}

double dfs(int u, double f) {
	if (u == t || f == 0) return f;
	double w, used = 0;
	
	for (int &i = iter[u]; ~i; i=es[i].next) {
		int v = es[i].to;
		if (es[i].w && level[v] == level[u]+1) {
			w = dfs(v, min(es[i].w, f-used));
			es[i].w -= w; es[i^1].w += w;
			used += w;
			if (used == f) return f;
		}
	}
	
	if(!used) level[u] = -1;
	return used;
}

double Dinic() {
	double res = 0;
	
	while (bfs()) {
		double f;
		for (int i = 1; i <= n; i++) iter[i] = head[i];
		while ((f=dfs(s, INF)) > eps) {
			res += f;
		}
	}
	
	return res;
}

void solve() {
	s = 1; t = n;
	double mf = Dinic();
	printf("%d\n", (int)mf);
	
	double ans = 0;
	double left = 0, right = 50010;
	while (right-left > eps) {
		double mid = left + (right-left) / 2;
		for (int i = 0; i < es.size(); i++) {
			es[i].w = min(ww[i], mid);
		}
		double f = Dinic();
		if (fabs(f-mf) < eps) {
			ans = mid;
			right = mid;
		} else {
			left = mid;
		}
	}
	
	for (int i = 0; i < es.size(); i++) {
		es[i].w = min(ww[i], ans);
	}
	Dinic();
	double mx = 0;
	for (int i = 1; i < es.size(); i+=2) {
		mx = max(mx, es[i].w);
	}
	printf("%.5lf", mx*p);
}

int main() {
	cin >> n >> m >> p;
	
	memset(head, -1, sizeof(head));
	int u, v;
	double w;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%lf", &u, &v, &w);
		add_edge(u, v, w);
	}
	solve();
	
	return 0;
}
