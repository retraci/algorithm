// POJ 3009
// Curling 2.0
#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 30;

int w, h, ans, time;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int map[maxn][maxn];
int sx, sy;

void dfs(int x, int y) {
	if(time > 9) return;
	
	int nx, ny;
	for(int i=0;i<4;i++) {
		nx = x+dx[i], ny = y+dy[i];
		
		// 挡住不能动 
		if(map[nx][ny] == 1) continue;
		// 可以动 
		while(map[nx][ny] == 2 || map[nx][ny] == 0) {
			nx += dx[i], ny += dy[i];
		}
		
		// 动 之后出界 
		if(map[nx][ny] == -1) continue;
		
		// 动 之后遇到障碍物停下来 
		if(map[nx][ny] == 1) {
			map[nx][ny] = 0;
			time++;
			dfs(nx-dx[i], ny-dy[i]);
			time--;
			map[nx][ny] = 1;
		}
		
		// 动 之后遇到终点 
		if(map[nx][ny] == 3) {
			// nx，ny属于未走到的地方，所以 ans = time+1； 
			if(time < ans) ans = time+1;
		}
	}
}

void solve() {
	ans = 20;
	time = 0;
	dfs(sx,sy);
	if(ans <= 10) cout << ans << endl;
	else cout << -1 << endl;
}

int main() {
	while(cin >> w >> h && w && h) {
		memset(map,-1,sizeof(map));
		for(int i=1;i<=h;i++) {
			for(int j=1;j<=w;j++) {
				cin >> map[i][j];
				if(map[i][j] == 2) sx = i, sy = j;
			}
		}
		solve();
	}
	
	return 0;
}

