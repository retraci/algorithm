// 蓝桥杯9B 全球变暖
/*
	思路：
	遍历，搜索，编号，计数 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1010;

struct point {
	int x, y;
	point(int x_, int y_) {
		x = x_; y = y_;
	}
};

const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

int n, num;
int G[maxn][maxn];
int vis[maxn][maxn];
int NG[maxn][maxn];

bool inBound(int x, int y) {
	if(x>=0 && x<n && y>=0 && y<n) return true;
	return false;
}

void bfs(int x, int y) {
	num++;
	queue<point> que;
	que.push(point(x, y));
	vis[x][y] = 1;
	G[x][y] = num;

	while(!que.empty()) {
		point p = que.front(); que.pop();
		for(int i = 0; i < 4; i++) {
			int nx = p.x + dx[i];
			int ny = p.y + dy[i];
			if(!vis[nx][ny] && inBound(nx, ny) && G[nx][ny] != 0) {
				vis[nx][ny] = 1;
				G[nx][ny] = num;
				que.push(point(nx, ny));
			}
		}
	}
}

void solve() {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(!vis[i][j] && G[i][j] == -1) {
				bfs(i, j);
			}
			vis[i][j] = 1;
		}
	}
	
	for(int i = 0; i < n; i++) 
		for(int j = 0; j < n; j++) NG[i][j] = G[i][j];
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(NG[i][j] != 0) {
				for(int k = 0; k < 4; k++) {
					int nx = i + dx[k];
					int ny = j + dy[k];
					if(inBound(nx, ny) && G[nx][ny] == 0) {
						NG[i][j] = 0;
						break;
					}
				}
			}
		}
	}
	
	set<int> ans;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(NG[i][j] != 0) {
				ans.insert(NG[i][j]);
			}
		}
	}
	
	cout << num-ans.size() << endl;
}

int main() {
	cin >> n;

	for(int i = 0; i < n; i++) {
		string str;
		cin >> str;
		for(int j = 0; j < n; j++) {
			if(str[j] == '#') G[i][j] = -1;
		}
	}
	solve();

	return 0;
}
