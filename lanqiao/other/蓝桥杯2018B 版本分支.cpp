// 蓝桥杯2018B 版本分支
/*
	思路：
	lca 问题
	在线倍增算法 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

int n, m;
vector<int> G[maxn];
int fa[maxn][25];
int dep[maxn];

void dfs(int root, int pa) {
	dep[root] = dep[pa] + 1;
	fa[root][0] = pa;
	
	for(int i = 0; i < G[root].size(); i++) {
		if(G[root][i] == pa) continue;
		dfs(G[root][i], root);
	}
}

int lca(int x, int y) {
	if(dep[y] > dep[x]) swap(x, y);
	
	if(dep[x] != dep[y])
	for(int i = log2(dep[x]-dep[y]); i >= 0; i--) {
		if((1<<i) <= dep[x]-dep[y]) x = fa[x][i];
	}
	if(x == y) return y;
	
	for(int i = log2(dep[x]); i >= 0; i--) {
		if(fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	
	return fa[x][0];
}

int main() {
	cin >> n >> m;
	
	int a, b;
	for(int i = 0; i < n-1; i++) {
		scanf("%d%d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs(1, 0);
	for(int i = 1; i <= 20; i++) {
		for(int j = 1; j <= n; j++) {
			fa[j][i] = fa[fa[j][i-1]][i-1];
		}
	}
	
	while(m--) {
		scanf("%d%d", &a, &b);
		int q = lca(a, b);
		if(q == a) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	
	return 0;
}
