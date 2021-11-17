// POJ 3050 Hopscotch
/*
	Ã¶¾Ù 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

const int maxn = 1e6;
const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,-1,1};

int vis[maxn];
int G[5][5];
vector<int> path;
int ans;

bool is_inBorder(int x, int y) {
	return (x>=0 && x<5 && y>=0 && y<5);
}

int str2int() {
	return path[0]*1e5+path[1]*1e4+path[2]*1e3+path[3]*1e2+path[4]*10+path[5];
}

void dfs(int x, int y) {
	if(path.size() == 6) {
		int temp = str2int();
		if(!vis[temp]) {
			vis[temp] = true;
			ans++;
		}
		return;
	}
	for(int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(is_inBorder(nx, ny)) {
			path.push_back(G[nx][ny]);
			dfs(nx, ny);
			path.pop_back();
		}
	}
}

int main() {
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			scanf("%d", &G[i][j]);
		}
	}
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			path.push_back(G[i][j]);
			dfs(i, j);
			path.pop_back();
		}
	}
	printf("%d\n", ans);

	return 0;
}

