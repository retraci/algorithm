// 二色图判断
/*
	dfs 即可
	把涂的颜色放入形参，若即将要涂的颜色与点已有的颜色不同，则返回 false
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 1010;

int n, m;
vector<int> map[maxn];
int col[maxn];

bool dfs(int x, int c) {
	if(col[x] == -c) return false;
	else if(col[x] == c) return true;
	col[x] = c;
	bool flag = true;
	for(int i=0; i<map[x].size(); i++) {
		if (dfs(map[x][i], -c)) flag = true;
		else flag = false;
	}
	return flag;
}

void solve() {
	bool flag = true;
	for(int i=0; i<n; i++) {
		if(col[i] == 0) {
			if(!dfs(i, 1)) flag = false;
		}
	}
	cout << flag << endl;
}

int main() {
	memset(col, 0, sizeof(col));
	for(int i=0; i<maxn; i++) map[i].clear();
	int a, b;
	while(cin >> n >> m) {
		for(int i=0; i<m; i++) {
			scanf("%d %d", &a, &b);
			map[a].push_back(b);
			map[b].push_back(a);
		}
		solve();
	}
	return 0;
}
