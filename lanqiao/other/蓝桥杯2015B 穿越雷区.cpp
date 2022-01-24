// 蓝桥杯2015B 穿越雷区
/*
	思路：
	bfs
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
	int x, y, s;
	Node(int x_, int y_, int s_) {
		x = x_, y = y_, s = s_;
	}
};

const int maxn = 105;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

int n, ans;
int sx, sy, tx, ty;
vector<string> maze;
int vis[maxn][maxn];

bool inBound(int x, int y) {
	return x>=0 && x<n && y>=0 && y<n;
}

void bfs() {
	queue<Node> que;
	vis[sx][sy] = 1;
	que.push(Node(sx, sy, 0));

	int cnt = 0;
	while(!que.empty()) {
		int len = que.size();

		for(int i = 0; i < len; i++) {
			Node now = que.front(); que.pop();
			//cout << now.x << " " << now.y << endl;

			for(int j = 0; j < 4; j++) {
				int nx = now.x + dx[j];
				int ny = now.y + dy[j];

				if(inBound(nx, ny)) {
					int ns = 0;
					if(maze[nx][ny] == '+') ns = 1;
					else if(maze[nx][ny] == '-') ns = -1;

					if(nx == tx && ny == ty) {
						ans = cnt+1;
						return;
					}
					if(!vis[nx][ny] && (now.s==0 || ns==0 || ns+now.s==0)) {
						vis[nx][ny] = 1;
						que.push(Node(nx, ny, ns));
					}
				}
			}
		}
		cnt++;
	}

	ans = -1;
}

void solve() {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(maze[i][j] == 'A') {
				sx = i, sy = j;
			} else if(maze[i][j] == 'B') {
				tx = i, ty = j;
			}
		}
	}

	memset(vis, 0, sizeof(vis));
	bfs();

	cout << ans << endl;
}

int main() {
	int pos;
	string temp;

	cin >> n;
	getchar();
	for(int i = 0; i < n; i++) {
		getline(cin, temp);
		while((pos=temp.find(' ')) != string::npos) {
			temp.erase(pos, 1);
		}
		maze.push_back(temp);
	}
	solve();

	return 0;
}
