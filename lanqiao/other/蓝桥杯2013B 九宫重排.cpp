// 蓝桥杯2013B 九宫重排
/*
	思路：
	bfs
	可以优化成双向 bfs

	node:
	双向 bfs vis数组维护的时候是在插入的时候
	表示已经在别的地方插入过了
*/

#include <bits/stdc++.h>

using namespace std;

int sz[9] = {2,3,2,3,4,3,2,3,2};
int dir[9][4];

string s, t;

void bfs() {
	queue<string> que;
	map<string, int> vis;

	int cnt = 0;
	que.push(s);
	vis[s] = 1;
	while(!que.empty()) {
		int len = que.size();

		for(int i = 0; i < len; i++) {
			string now = que.front();
			que.pop();

			int idx = now.find(".");
			for(int j = 0; j < sz[idx]; j++) {
				swap(now[idx], now[dir[idx][j]]);

				if(now == t) {
					cout << cnt+1 << endl;
					return;
				}
				if(!vis[now]) {
					vis[now] = 1;
					que.push(now);
				}

				swap(now[idx], now[dir[idx][j]]);
			}
		}
		cnt++;
	}

	cout << -1 << endl;
}

void bfs2() {
	set<string> set1, set2, temp;
	map<string, int> vis;
	set1.insert(s);
	set2.insert(t);
	vis[s] = vis[t] = 1;

	int cnt = 0;
	while(set1.size() && set2.size()) {
		if(set1.size() > set2.size()) {
			temp = set1;
			set1 = set2;
			set2 = temp;
		}

		temp.clear();
		for(string now: set1) {
			int idx = now.find(".");
			for(int i = 0; i < sz[idx]; i++) {
				swap(now[idx], now[dir[idx][i]]);

				if(set2.count(now)) {
					cout << cnt+1 << endl;
					return;
				}

				if(!vis[now]) {
					temp.insert(now);
					vis[now] = 1;
				}

				swap(now[idx], now[dir[idx][i]]);
			}
		}

		set1 = temp;
		cnt++;
	}
}

int main() {
	dir[0][0] = 1;
	dir[0][1] = 3;
	dir[1][0] = 0;
	dir[1][1] = 2;
	dir[1][2] = 4;
	dir[2][0] = 1;
	dir[2][1] = 5;
	dir[3][0] = 0;
	dir[3][1] = 4;
	dir[3][2] = 6;
	dir[4][0] = 1;
	dir[4][1] = 3;
	dir[4][2] = 5;
	dir[4][3] = 7;
	dir[5][0] = 2;
	dir[5][1] = 4;
	dir[5][2] = 8;
	dir[6][0] = 3;
	dir[6][1] = 7;
	dir[7][0] = 4;
	dir[7][1] = 6;
	dir[7][2] = 8;
	dir[8][0] = 5;
	dir[8][1] = 7;

	cin >> s >> t;
	bfs2();

	return 0;
}
