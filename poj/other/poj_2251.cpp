// POJ 2251 Dungeon Master

#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>

using namespace std;

struct Node {
	int z, x, y, step;
	Node(int z_, int x_, int y_, int s_) {
		z = z_; x = x_; y = y_; step = s_;
	}
};

const int maxn = 50;

const int dz[6] = {-1,1,0,0,0,0};
const int dx[6] = {0,0,-1,1,0,0};
const int dy[6] = {0,0,0,0,-1,1};

int l, r, c, ans;
int sz, sx, sy, ez, ex, ey;
char maze[maxn][maxn][maxn];
int vis[maxn][maxn][maxn];

bool inBound(int z, int x, int y) {
	if(z>=0 && z<l && x>=0 && x<r && y>=0 && y<c) return true;
	return false;
}

void bfs(int z, int x, int y) {
	memset(vis, 0, sizeof(vis));
	
	queue<Node> que;
	que.push(Node(z, x, y, 0));
	vis[z][x][y] = 1;
	
	while(!que.empty()) {
		Node node = que.front(); que.pop();
		if(node.z==ez && node.x==ex && node.y==ey) {
			ans = node.step;
			break;
		}
		for(int i = 0; i < 6; i++) {
			int nz = node.z + dz[i];
			int nx = node.x + dx[i];
			int ny = node.y + dy[i];
			
			if(inBound(nz, nx, ny) && !vis[nz][nx][ny] && maze[nz][nx][ny] == '.') {
//				printf("%d %d %d\n", nz, nx, ny);
				vis[nz][nx][ny] = 1;
				que.push(Node(nz, nx, ny, node.step+1));
			}
		}
	}
}

void solve() {
	for(int i = 0; i < l; i++) {
		for(int j = 0; j < r; j++) {
			for(int k = 0; k < c; k++) {
				if(maze[i][j][k] == 'S') {
					maze[i][j][k] = '.';
					sz = i; sx = j; sy = k;
					break;
				} else if(maze[i][j][k] == 'E') {
					maze[i][j][k] = '.';
					ez = i; ex = j; ey = k;
					break;
				} 
			}
		}
	}
	ans = 0x3f3f3f3f;
	bfs(sz, sx, sy);
	
	if(ans == 0x3f3f3f3f) {
		printf("Trapped!\n");
	} else {
		printf("Escaped in %d minute(s).\n", ans);
	}
}

int main() {
	while(~scanf("%d%d%d", &l, &r, &c) && l && r && c) {
		for(int i = 0; i < l; i++) {
			for(int j = 0; j < r; j++) {
				scanf("%s", maze[i][j]);
			}
		}
		
		solve();
	}
	
	return 0;
}
