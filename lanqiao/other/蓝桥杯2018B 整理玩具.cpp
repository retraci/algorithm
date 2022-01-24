// 蓝桥杯2018B 整理玩具 
/*
	思路：
	遍历 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 15;

int n, m;
int maze[maxn][maxn];
int vis[maxn];

bool cal(int sr, int sc, int key) {
	int tr = sr, tc = sc;
	for(int j = sc; j < m; j++) {
		if(key == maze[sr][j]) tc = j;
		else break;
	}
	for(int i = sr; i < n; i++) {
		if(key == maze[i][sc]) tr = i;
		else break;
	}
	for(int i = sr; i <= tr; i++) {
		for(int j = sc; j <= tc; j++) {
			if(key != maze[i][j]) return false;
			maze[i][j] = -1;
		}
	}
	return true;
}

void solve() {
	memset(vis, 0, sizeof(vis));
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(maze[i][j] == -1) {
				continue;
			}
			if(vis[maze[i][j]]) {
				cout << "NO" << endl;
				return;
			}
			
			vis[maze[i][j]] = 1;
			if(!cal(i, j, maze[i][j])) {
				cout << "NO" << endl;
				return;
			}
			
			/*
			cout << endl;
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m; j++) {
					printf("%d", maze[i][j]);
				}
				cout << endl;
			}
			*/
		}
	}
	
	cout << "YES" << endl;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i++) {
			string s;
			cin >> s;
			for(int j = 0; j < m; j++) {
				char ch = s[j];
				maze[i][j] = s[j]-'0';
			}
		}
		
		solve();
	} 
	
	return 0;
}
