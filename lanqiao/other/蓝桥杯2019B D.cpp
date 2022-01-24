// 蓝桥杯2019B D
/*
	思路：
	dfs
*/

#include <bits/stdc++.h>

using namespace std;

const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

int ans;
int vis[10][10];

bool inBound(int x, int y) {
	return x>=0 && x<=7 && y>=0 && y<=7;
}

void dfs(int x, int y, int step) {
	if(step > 12) return;

	for(int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if(nx == 0 && ny == 0 && step > 2 && step+1 <= 12) {
			ans++;
			continue;
		}

		if(inBound(nx, ny) && !vis[nx][ny]) {
			vis[nx][ny] = 1;
			dfs(nx, ny, step+1);
			vis[nx][ny] = 0;
		}
	}
}

int main() {
	vis[0][0] = 1;
	dfs(0, 0, 0);
	cout << ans << endl;

	return 0;
}
