// 201812-4
/*

*/

#include <bits/stdc++.h>

using namespace std;

struct Edge {
	int from, to, cost;
	Edge(int f_, int t_, int c_) {
		from = f_, to = t_, cost = c_;
	}
};

const int INF = 0x3f3f3f3f;
const int maxn = 1e5;

int n, m, root;
vector<Edge> es;
int fa[maxn];
int ans;

bool cmp(const Edge& e1, const Edge& e2) {
	return e1.cost < e2.cost;
}

int find(int x) {
	return x==fa[x] ? x : fa[x] = find(fa[x]);
}

void Kruskal() {
	for(int i = 0; i <= n; i++) fa[i] = i;
	sort(es.begin(), es.end(), cmp);
	
	for(int i = 0; i < es.size(); i++) {
		int tx = find(es[i].from);
		int ty = find(es[i].to);
		
		if(tx != ty) {
			fa[tx] = ty;
			ans = max(ans, es[i].cost);
		}
	}
}

void solve() {
	Kruskal();
	
	cout << ans << endl;
}

int main() {
	cin >> n >> m >> root;
	
	int a, b, c;
	while(m--) {
		scanf("%d%d%d", &a, &b, &c);
		es.push_back(Edge(a, b, c));
		es.push_back(Edge(b, a, c));
	}
	solve();
	
	return 0;
}
