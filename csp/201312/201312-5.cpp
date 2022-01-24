// 	I’m stuck! - 201312-5
/*
	思路：
	dfs + 反向 dfs 
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 55;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};	// up down left right

int r, c;
int sx, sy, tx, ty;
char G[maxn][maxn];
bool s_arrive[maxn][maxn], t_arrive[maxn][maxn];

void dfs_s(int x, int y) {
	s_arrive[x][y] = true;
	if(G[x][y] == 'S' || G[x][y] == 'T' || G[x][y] == '+') {
		for(int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(nx >= 0 && nx < r && ny >= 0 && ny < c && G[nx][ny] != '#' && !s_arrive[nx][ny]) {
				dfs_s(nx, ny);
			}
		}
	} else if(G[x][y] == '-') {
		for(int i = 2; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(nx >= 0 && nx < r && ny >= 0 && ny < c && G[nx][ny] != '#' && !s_arrive[nx][ny]) {
				dfs_s(nx, ny);
			}
		}
	} else if(G[x][y] == '|') {
		for(int i = 0; i < 2; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(nx >= 0 && nx < r && ny >= 0 && ny < c && G[nx][ny] != '#' && !s_arrive[nx][ny]) {
				dfs_s(nx, ny);
			}
		}
	} else if(G[x][y] == '.') {
		int nx = x + 1;
		int ny = y;
		if(nx >= 0 && nx < r && ny >= 0 && ny < c && G[nx][ny] != '#' && !s_arrive[nx][ny]) {
			dfs_s(nx, ny);
		}
	}
}

void dfs_t(int x, int y) {
	t_arrive[x][y] = true;
	for(int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(nx >= 0 && nx < r && ny >= 0 && ny < c && G[nx][ny] != '#' && !t_arrive[nx][ny]) {
			if(G[nx][ny] == 'S' || G[nx][ny] == 'T' || G[nx][ny] == '+') {
				dfs_t(nx, ny);
			} else if(G[nx][ny] == '-' && (i==2 || i==3)) {
				dfs_t(nx, ny);
			} else if(G[nx][ny] == '|' && (i==0 || i==1)) {
				dfs_t(nx, ny);
			} else if(G[nx][ny] == '.' && (i==0)) {
				dfs_t(nx, ny);
			}
		}
	}
}

void solve() {
	int ans = 0;
	dfs_s(sx, sy);
	if(s_arrive[tx][ty] = false) {
		printf("I’m stuck!\n");
		return;
	}
	dfs_t(tx, ty);
	for(int i = 0; i < r; i++) {
		for(int j = 0; j < c; j++) {
			if(s_arrive[i][j] && !t_arrive[i][j]) {
				ans++;
			}
		}
	}
	printf("%d\n", ans);
}

int main() {
	scanf("%d%d", &r, &c);
	for(int i = 0; i < r; i++) {
		scanf("%s", G[i]);
	}
	for(int i = 0; i < r; i++) {
		for(int j = 0; j < c; j++) {
			if(G[i][j] == 'S') {
				sx = i;
				sy = j;
			} else if(G[i][j] == 'T') {
				tx = i;
				ty = j;
			}
		}
	}
	solve();

	return 0;
}
