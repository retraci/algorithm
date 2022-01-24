// POJ 1321 棋盘问题
/*
	思路：
	类似八皇后，dfs
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxn = 10;

int n, k, ans;
int maze[maxn][maxn];
int vis[maxn];

void dfs(int x, int num) {
	if(num == k) {
		ans++;
		return;
	}

	for(int i = x; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(!vis[j] && maze[i][j]) {
				vis[j] = 1;
				dfs(i+1, num+1);
				vis[j] = 0;
			}
		}
	}
}

void solve() {
	dfs(0, 0);
	cout << ans << endl;
}

int main() {
	string str;

	while(~scanf("%d%d", &n, &k) && n!=-1 && k!=-1) {
		ans = 0;
		memset(maze, 0, sizeof(maze));
		memset(vis, 0, sizeof(vis));

		for(int i = 0; i < n; i++) {
			cin >> str;
			for(int j = 0; j < str.length(); j++) {
				if(str[j] == '#') maze[i][j] = 1;
			}
		}
//		for(int i = 0; i < n; i++) {
//			for(int j = 0; j < n; j++) {
//				cout << maze[i][j];
//			}
//			cout << endl;
//		}
		solve();
	}

	return 0;
}
