// 蓝桥杯 城市建设
/*
	思路：
	最小生成树

	note：河流可以看作一个汇合点
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

struct edge {
	int from, to, cost;
};

const int INF = 0x3f3f3f3f;
const int maxn = 10000 + 100000 + 10;

int n, m;
edge G[maxn];
int fa[maxn];

bool cmp(edge e1, edge e2) {
	return e1.cost < e2.cost;
}

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

bool join(int x, int y) {
	int tx = find(x);
	int ty = find(y);
	
	if(tx == ty) return false;
	fa[tx] = ty;
	return true;
}

// 考虑码头 
int Kruskal1() {
	int res = 0;
	for(int i = 0; i <= n+m; i++) fa[i] = i;
	
	for(int i = 0; i < n+m; i++) {
		if(G[i].cost == INF) continue;
		
		if(join(G[i].from, G[i].to)) {
			res += G[i].cost;
		} else if(G[i].cost < 0){
			res += G[i].cost;
		}
	}
	return res;
}

// 不考虑建码头 
int Kruskal2() {
	int res = 0;
	for(int i = 0; i <= n+m; i++) fa[i] = i;
	
	for(int i = 0; i < n+m; i++) {
		if(G[i].from == 0) continue;
		
		if(join(G[i].from, G[i].to)) {
			res += G[i].cost;
		} else if(G[i].cost < 0){
			res += G[i].cost;
		}
	}
	return res;
}

void solve() {
	sort(G, G+n+m, cmp);
	
	// 考虑码头 
	int ans1 = Kruskal1();
	// 不考虑码头 
	int ans2 = Kruskal2();
	
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		if(fa[i] == i) cnt++;
	}
	if(cnt != 1) cout << ans1 << endl;
	else cout << min(ans1, ans2) << endl;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		scanf("%d%d%d", &G[i].from, &G[i].to, &G[i].cost);
	}
	for(int i = m; i < m+n; i++) {
		G[i].from = 0; G[i].to = i-m+1;
		scanf("%d", &G[i].cost);
		if(G[i].cost == -1) G[i].cost = INF;
	}
	solve();

	return 0;
}
