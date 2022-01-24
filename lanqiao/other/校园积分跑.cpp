// 校园积分跑
/*
	思路：
	tarjan缩点 + 记忆化搜索 
*/
 
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4+10;

int n, m;
int a[maxn];

int tot;
vector<int> G1[maxn], G2[maxn];
int val[maxn];
int stk[maxn], inStack[maxn], dfn[maxn], low[maxn], top, ti;

vector<int> bcc[maxn];
int belong[maxn];
int du[maxn];
int dp[maxn];

void tarjan(int u) {
	dfn[u] = low[u] = ++ti;
	stk[top++] = u;
	inStack[u] = 1;
	
	for(int i = 0; i < G1[u].size(); i++) {
		int v = G1[u][i];
		if(dfn[v] == -1) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(inStack[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	
	if(dfn[u] == low[u]) {
		tot++;
		bcc[tot].clear();
		int x;
		do {
			x = stk[--top];
			inStack[x] = 0;
			bcc[tot].push_back(x);
			belong[x] = tot;
		} while(x != u);
	}
}

void suodian() {
	for(int i = 0; i <= tot; i++) G2[i].clear();
	memset(val, 0, sizeof(val));
	memset(du, 0, sizeof(du));
	
	for(int i = 1; i <= tot; i++) {
		for(int j = 0; j < bcc[i].size(); j++) {
			val[i] += a[bcc[i][j]];
		}
	}
	
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < G1[i].size(); j++) {
			int u = belong[i];
			int v = belong[G1[i][j]];
			
			if(u == v) continue;
			G2[u].push_back(v);
			du[v]++;
		}
	}
}

int dfs(int u) {
	if(dp[u] != -1) return dp[u];
	
	int res = val[u];
	for(int i = 0; i < G2[u].size(); i++) {
		int v = G2[u][i];
		res = max(res, val[u]+dfs(v));
	} 
	
	return dp[u]=res;
}

void solve() {
	memset(dfn, -1, sizeof(dfn));
	memset(inStack, 0, sizeof(inStack));
	top = ti = tot = 0;
	for(int i = 1; i <= n; i++) {
		if(dfn[i] == -1) tarjan(i);
	}
	suodian();
	 
	memset(dp, -1, sizeof(dp));
	int ans = 0;
	for(int i = 1; i <= tot; i++) {
		if(du[i] == 0) ans = max(ans, dfs(i)); 
	}
	
	cout << ans << endl;
}

int main() {
	cin >> n >> m;
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	for(int i = 0; i <= n; i++) G1[i].clear();
	
	int u, v;
	while(m--) {
		scanf("%d%d", &u, &v);
		G1[u].push_back(v);
	}
	solve();
	
	return 0;
} 
