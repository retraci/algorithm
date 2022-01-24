// 蓝桥杯 发现环
/*
	思路：
	并查集 + dfs
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5+10;

int n;
vector<int> G[MAXN];
int fa[MAXN];
int vis[MAXN];
vector<int> ans;
stack<int> path;

int find(int x) {
	return x==fa[x]? x:fa[x]=find(fa[x]);
}

void dfs(int st, int ed) {
	path.push(st);
	vis[st] = 1;
	
	if(st == ed) {
		while(!path.empty()) {
			ans.push_back(path.top());
			path.pop();
		}
		sort(ans.begin(), ans.end());
		for(int i = 0; i < ans.size()-1; i++) {
			cout << ans[i] << " ";
		}
		cout << ans[ans.size()-1] << endl;
		
		exit(0);
	}
	for(int i = 0; i < G[st].size(); i++) {
		int v = G[st][i];
		if(!vis[v]) {
			dfs(v, ed);
		}
	}
	path.pop();
	vis[st] = 0;
}

int main() {
	cin >> n;
	
	for(int i = 0; i < n; i++) G[i].clear();
	for(int i = 0; i < n; i++) fa[i] = i;
	memset(vis, 0, sizeof(vis));
	ans.clear();
	
	int a, b;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
		
		int tx = find(a), ty = find(b);
		if(tx != ty) {
			fa[tx] = ty;
		} else {
			dfs(a, b);
		}
	}

	return 0;
}
