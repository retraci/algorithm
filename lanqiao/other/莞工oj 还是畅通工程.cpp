// 莞工oj 还是畅通工程 
/*
	思路：
	Kruskal 
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
	int from, to, cost;
	Node(int f_, int t_, int c_) {
		from = f_, to = t_, cost = c_;
	}
};

const int maxn = 110;

int n;
vector<Node> es;
int fa[maxn];

bool cmp(Node& n1, Node& n2) {
	return n1.cost < n2.cost;
}

int find(int x) {
	return x==fa[x] ? x : fa[x] = find(fa[x]);
}

void solve() {
	for(int i = 0; i <= n; i++) fa[i] = i;
	
	sort(es.begin(), es.end(), cmp);
	
	int ans = 0;
	for(int i = 0; i < es.size(); i++) {
		Node &e = es[i];
		int tx = find(e.from);
		int ty = find(e.to);
		if(ty != tx) {
			fa[tx] = ty;
			ans += e.cost;
		}
	}
	
	cout << ans << endl;
}

int main() {
	while(cin >> n && n) {
		int m = n*(n-1) / 2;
		
		es.clear();
		int a, b, c;
		while(m--) {
			scanf("%d%d%d", &a, &b, &c);
			es.push_back(Node(a, b, c));
		}
		solve();
	}
	
	return 0;
} 
