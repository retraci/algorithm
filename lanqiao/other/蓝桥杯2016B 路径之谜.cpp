// 蓝桥杯2016B 路径之谜
/*
	思路：
	dfs 
*/

#include <bits/stdc++.h>

using namespace std;

const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

int n;
int a[2][20];
int cnt[2][20];
int vis[20][20];

bool inBound(int x, int y) {
	return x>=0 && x<n && y>=0 && y<n;
}

void dfs(int x, int y, vector<int>& path) {
	if(x == y && x == n-1) {
		for(int k = 0; k < 2; k++)
			for(int i = 0; i < n; i++) {
				//printf("%d ", cnt[k][i]);
				if(cnt[k][i] != a[k][i]) return;
			}
		
		for(int i = 0; i < path.size(); i++) {
			if(i < path.size()-1)
				printf("%d ", path[i]);
			else
				printf("%d\n", path[i]);
		}
	}
	
	for(int k = 0; k < 2; k++)
		for(int i = 0; i < n; i++) {
			if(cnt[k][i] > a[k][i]) return;
		}

	for(int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if(inBound(nx, ny) && !vis[nx][ny]) {
			cnt[0][ny] += 1;
			cnt[1][nx] += 1;
			vis[nx][ny] = 1;
			path.push_back(nx*n+ny);
			dfs(nx, ny, path);
			path.pop_back();
			vis[nx][ny] = 0;
			cnt[0][ny] -= 1;
			cnt[1][nx] -= 1;
		}
	}

}

void solve() {
	vector<int> path;
	memset(cnt, 0, sizeof(cnt));
	memset(vis, 0, sizeof(vis));
	
	cnt[0][0] = 1;
	cnt[1][0] = 1;
	vis[0][0] = 1;
	path.push_back(0);
	dfs(0,0,path);
}

int main() {
	cin >> n;
	for(int k = 0; k < 2; k++)
		for(int i = 0; i < n; i++) {
			scanf("%d", &a[k][i]);
		}
	solve();

	return 0;
}
