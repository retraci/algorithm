// 蓝桥杯 国王的烦恼
/*
	思路：
	并查集
	
	顺着 t 是不断销毁边 再 union
	如果逆着时间就是 不断的 union 边
	从而降低时间复杂度
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct edge {
	int from, to, t;
	edge(int ff, int tt, int ti):from(ff), to(tt), t(ti) {
	}
};

const int maxn = 10001;
const int maxm = 100001;

int n, m;
vector<int> fa;
vector<edge> G;

bool cmp(edge e1, edge e2) {
	return e1.t > e2.t;
}

int find(int x) {
	return fa[x]==x? x:fa[x] = find(fa[x]);
}

bool join(int x, int y) {
	int tx = find(x), ty = find(y);

	if(tx == ty) {
		return false;
	} else {
		fa[tx] = ty;
		return true;
	}
}

void solve() {
	sort(G.begin(), G.end(), cmp);
//	for(auto a : G) {
//		printf("%d %d %d\n", a.from, a.to, a.t);
//	}
	for(int i = 0; i <= n; i++) fa[i] = i;
	
	int cnt = 0, lastday = -1;
	for(int i = 0; i < m; i++) {
		if(join(G[i].from, G[i].to) && G[i].t!=lastday) {
			lastday = G[i].t;
			cnt++;
		}
	}
	
	cout << cnt << endl;	
}

int main() {
	cin >> n >> m;
	fa.resize(n+1);
	for(int i = 0; i < m; i++) {
		int t1, t2, t3;
		scanf("%d%d%d", &t1, &t2, &t3);
		G.push_back(edge(t1, t2, t3));
	}
	solve();

	return 0;
}
