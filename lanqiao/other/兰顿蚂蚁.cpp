// 蓝桥杯 兰顿蚂蚁 
/*
	思路：
	模拟 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100;
// 0 - U   1 - R   2 - D   3 - L
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m;
int G[maxn][maxn];
int dir;
int x, y, k;
char s;

void solve() {
	if(s == 'U') dir = 0;
	if(s == 'R') dir = 1;
	if(s == 'D') dir = 2;
	if(s == 'L') dir = 3;
	
	while(k--) {
		if(G[x][y] == 1) {
			dir = (dir+1) % 4;
		} else {
			dir = (dir+3) % 4;
		}
		G[x][y] = !G[x][y];
		x = x+dx[dir];
		y = y+dy[dir];
		
	}
	cout << x << " " << y << endl;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			scanf("%d", &G[i][j]);
		}
	}
	scanf("%d %d %c %d", &x, &y, &s, &k);
	solve();
	
	return 0;
} 
