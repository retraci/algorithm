// POJ 1251 Jungle Roads
/*
	思路：
	最小树 Kruskal 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
	int from, to, cost;
	Edge(int f_, int t_, int c_) {
		from = f_; to = t_; cost = c_;
	}
};

const int maxn = 110;

int n;
vector<Edge> es;
int fa[maxn];

bool cmp(Edge e1, Edge e2) {
	return e1.cost < e2.cost;
}

int find(int x) {
	return x==fa[x] ? x: fa[x]=find(fa[x]);
}

int Kruskal() {
	sort(es.begin(), es.end(), cmp);
	for(int i = 0; i < n; i++) fa[i] = i;
	
	int cnt = 0, res = 0;
	
	for(int i = 0; i < es.size(); i++) {
		int tx = find(es[i].from);
		int ty = find(es[i].to);
		if(tx == ty) continue;
		
		fa[tx] = ty;
		cnt++;
		res += es[i].cost;
		if(cnt == n-1) break;
	}
	
	return res;
}

void solve() {
	int ans = Kruskal();
	
	cout << ans << endl;
}

int main() {
	while(cin >> n && n) {
		for(int i = 0; i < n; i++) es.clear();
		
		char ch;
		int T, from, to, cost;
		for(int i = 0; i < n-1; i++) {
			cin >> ch >> T;
			from = ch - 'A';
			while(T--) {
				cin >> ch >> cost;
				to = ch - 'A';
				es.push_back(Edge(from, to, cost));
			}
		}
		solve();
	}
	
	return 0;
}
