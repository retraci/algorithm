// 蓝桥杯10B 迷宫
/*
	思路： 
	bfs 
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
	int x, y;
	string path;
	Node(int x_, int y_, string p_) {
		x = x_; y = y_; path = p_;
	} 
};

//       down  left  right  up 
const int dx[4] = {1,0,0,-1};
const int dy[4] = {0,-1,1,0};
const char dir[4] = {'D','L','R','U'};
const int MAXN = 30;
const int MAXM = 50;

int n, m;
int maze[MAXN][MAXM];
bool vis[MAXN][MAXM];

bool inBound(int x, int y) {
	if(x<0 || y<0 || x>=n || y>=m) return false;
	return true;
}

void bfs() {
	memset(vis, false, sizeof(vis));
	queue<Node> que;
	que.push(Node(0, 0, ""));
	vis[0][0] = true;
	
	while(!que.empty()) {
		Node node = que.front(); que.pop();
		
		if(node.x == n-1 && node.y == m-1) {
			cout << node.path << endl;
			return;
		}
		
		for(int i = 0; i < 4; i++) {
			int nx = node.x+dx[i];
			int ny = node.y+dy[i];
			if(maze[nx][ny] == 0 && !vis[nx][ny] && inBound(nx, ny)) {
				vis[nx][ny] = true;
				que.push(Node(nx, ny, node.path+dir[i]));
			}
		}
	}
}

int main() {
	n = 30, m = 50;
	
	char temp;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			scanf("%c", &temp);
			maze[i][j] = temp-'0';
		}
		getchar();
	}
	bfs();
	
	return 0;
}
