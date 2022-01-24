// POJ 1979
// Red and Black
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxw = 30, maxh = 30;

int w, h, ans, sx, sy;
char map[maxh][maxw];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
bool vis[maxh][maxw];

void dfs(int y,int x) {
	int nx, ny;
	for(int i=0; i<4; i++) {
		nx = x+dx[i];
		ny = y+dy[i];
		if(0 <= nx && nx < w && 0 <= ny && ny < h && !vis[ny][nx] && map[ny][nx] == '.') {
			ans++;
			vis[ny][nx] = true;
			dfs(ny,nx);
		}
	}
}

void solve() {
	memset(vis,false,sizeof(vis));
	vis[sy][sx] = true;
	ans = 1;
	dfs(sy,sx);
	cout << ans << endl;
}

int main() {
	while(cin >> w >> h && w && h) {
		for(int i=0; i<h; i++)
			for(int j=0; j<w; j++) {
				cin >> map[i][j];
				if(map[i][j] == '@') sx = j, sy = i;
			}

		solve();
	}

	return 0;
}
