// POJ 1258 Agri-Net
/*
	思路：
	最小树
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

struct Edge {
	int from, to, cost;
	Edge(int f_, int t_, int c_) {
		from = f_;
		to = t_;
		cost = c_;
	}
};

const int INF = 0x3f3f3f3f;
const int maxn = 110;

int n;
vector<Edge> es;
int fa[maxn];

bool cmp(Edge e1, Edge e2) {
	return e1.cost < e2.cost;
}

int find(int x) {
	return x==fa[x] ? x : fa[x]=find(fa[x]);
}

int Kruskal() {
	int res = 0;

	sort(es.begin(), es.end(), cmp);

	int cnt = 0;
	for(int i = 0; i < es.size(); i++) {
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

	return res;
}

void solve() {
	for(int i = 0; i < n; i++) fa[i] = i;

	cout << Kruskal() << endl;
}

int main() {
	while(cin >> n) {
		es.clear();
		int tmp;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				scanf("%d", &tmp);
				if(i == j) continue;
				es.push_back(Edge(i, j, tmp));
			}
		}
		solve();
	}

	return 0;
}
