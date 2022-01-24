// 201709-4 通信网络
/*

*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;

int n, m;
vector<int> G[maxn];
int vis[maxn];
int mark[maxn][maxn];

void dfs(int now, int root) {
	if(vis[now]) return;
	vis[now] = 1;
	mark[now][root] = mark[root][now] = 1;
	
	for(int i = 0; i < G[now].size(); i++) {
		dfs(G[now][i], root);
	}
}

void solve() {
	memset(mark, 0, sizeof(mark));
	
	for(int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		dfs(i, i);
	}
	
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		int sum = 0;
		for(int j = 1; j <= n; j++) {
			if(mark[i][j]) sum++;
		}
		if(sum == n) {
			ans++;
		}
	}
	
	cout << ans << endl;
}

int main() {
	cin >> n >> m;
	
	int a, b;
	while(m--) {
		scanf("%d%d", &a, &b);
		G[a].push_back(b);
	}
	solve();
	
	return 0;
}
