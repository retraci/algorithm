// POJ 2377 Bad Cowtractors
/*
	思路：
	最大树 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

struct Edge {
	int from, to, cost;
	Edge(int f_, int t_, int c_) {
		from = f_; to = t_; cost = c_;
	}
};

const int maxn = 1010;

int n, m;
vector<Edge> es;
int fa[maxn];

bool cmp(Edge e1, Edge e2) {
	return e1.cost > e2.cost;
}

int find(int x) {
	return x==fa[x] ? x : fa[x]=find(fa[x]);
}

int Kruskal() {
	int res = 0;
	
	sort(es.begin(), es.end(), cmp);
	
	int cnt = 0;
	for(int i = 0; i < m; i++) {
		Edge &e = es[i];
		int tx = find(e.from);
		int ty = find(e.to);
		
		if(tx != ty) {
			fa[tx] = ty;
			cnt++;
			res += e.cost;
		}
		if(cnt >= n-1) break;
	}
	
	if(cnt < n-1) return -1;
	return res;
}

void solve() {
	for(int i = 1; i <= n; i++) fa[i] = i;
	
	cout << Kruskal() << endl;
}

int main() {
	cin >> n >> m;
	
	int a, b, c;
	for(int i = 0; i < m; i++) {
		scanf("%d%d%d", &a, &b, &c);
		es.push_back(Edge(a, b, c));
	}
	solve();
	
	return 0;
}

