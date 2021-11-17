// POJ 2186 Popular Cows
/*
	思路：
	tarjan缩点 得到 dag 图
	出度为 0 的点为 
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int maxn = 1e4+10;

int n, m;
vector<int> G1[maxn];
int dfn[maxn], low[maxn], stk[maxn], inStack[maxn], tot, top, ti;
vector<int> bcc[maxn];
int belong[maxn];
int du[maxn];

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
		} while(u != x);
	}
}

void suodian() {
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < G1[i].size(); j++) {
			int u = belong[i];
			int v = belong[G1[i][j]];
			if(u != v) {
				du[u]++;
			}
		}
	}
}

void solve() {
	memset(dfn, -1, sizeof(dfn));
	memset(inStack, 0, sizeof(inStack));
	tot = top = ti = 0;
	for(int i = 1; i <= n; i++) {
		if(dfn[i] == -1) tarjan(i);
	}
	suodian();
	
	int ans = 0, cnt = 0;
	for(int i = 1; i <= tot; i++) {
		if(!du[i]) {
			cnt++;
			ans += bcc[i].size();
		}
	}
	
	if(cnt > 1) ans = 0;
	cout << ans << endl;
}

int main() {
	while(~scanf("%d%d", &n, &m)) {
		for(int i = 0; i <= n; i++) G1[i].clear();
		
		int a, b;
		while(m--) {
			scanf("%d%d", &a, &b);
			G1[a].push_back(b);
		}
		solve();
	}
	
	return 0;
}
