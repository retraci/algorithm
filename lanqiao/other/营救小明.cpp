// 营救小明
/*

7 8
#.#####.
#.m#..f.
#..#g...
..#..#.#
#...##..
.#......
........

13

*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
	int x, y, cost;
	Node(int _x, int _y, int _c) {
		x = _x, y = _y, cost = _c;
	}
};

const int N = 210;
const int dx[4] = {-1,1,0,0};
const int dy[4] = {0,0,-1,1};

int n, m;
char g[N][N];
int s, t;
int vis[N][N];

void solve() {
	queue<Node> que;

	que.push(Node(s, t, 0));
	memset(vis, 0, sizeof(vis));
	while (!que.empty()) {
		int sz = que.size();
		for (int k = 0; k < sz; k++) {
			Node cur = que.front(); que.pop();
			int x = cur.x, y = cur.y;

			if (vis[x][y]) continue;
			vis[x][y] = 1;
			if (g[x][y] == 'f') {
				cout << cur.cost << endl;
				return;
			}

			for (int i = 0; i < 4; i++) {
				int nx = cur.x + dx[i];
				int ny = cur.y + dy[i];

				if (nx >= 1 && nx <= n && ny >= 0 && ny <= m) {
					if (g[nx][ny] != '#' && !vis[nx][ny]) {
						int nc = cur.cost + 1;
						if (g[nx][ny] == 'g') nc++;
						que.push(Node(nx, ny, nc));
					}
				}
			}
		}

	}

	cout << "Poor Xiaoming" << endl;
}

int main() {
	while (cin >> n >> m) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> g[i][j];
				if (g[i][j] == 'm') s = i, t = j;
			}
		}
		solve();
	}

	return 0;
}
