// 蓝桥杯8B 方格分割
/*
	思路：
	模拟剪刀
	dfs，对称标记 
*/

#include <bits/stdc++.h>

using namespace std;

const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};
const int maxn = 10;

int n, ans;
bool vis[maxn][maxn];

bool inBound(int x, int y) {
	if(x>=0 && x<=n && y>=0 && y<=n) return true;
	return false;
}

void dfs(int x, int y) {
	if(x==0 || x==n || y==0 || y==n) {
		ans++;
		return;
	}
	
	for(int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(inBound(nx, ny) && !vis[nx][ny]) {
			vis[nx][ny] = 1;
			vis[n-nx][n-ny] = 1;
			dfs(nx, ny);
			vis[nx][ny] = 0;
			vis[n-nx][n-ny] = 0;
		}
	}
}

int main() {
	n = 6;
	vis[n/2][n/2] = 1;
	dfs(n/2, n/2);
	
	cout << ans/4 << endl;
	
	return 0;
}
