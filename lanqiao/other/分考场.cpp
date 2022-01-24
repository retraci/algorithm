// 蓝桥杯 分考场
/*
	思路：
	dfs + 剪枝 
*/

#include <bits/stdc++.h>
#include <vector>

using namespace std;

const int MAXN = 110;

int n, m, ans;
vector<int> G[MAXN];
int room[MAXN][MAXN];

void dfs(int x, int num) {
	if(x == n+1) {
		ans = min(ans, num);
		return;
	}
	if(num >= ans) return;

	// 找房间放
	for(int i = 0; i < num; i++) {
		bool finded = false;
		for(int j = 0; j < G[x].size(); j++) {
			int v = G[x][j];
			if(room[i][v]) {
				finded = true;
				break;
			}
		}
		if(!finded) {
			room[i][x] = 1;
			dfs(x+1, num);
			room[i][x] = 0;
		}
	}
	
	// 直接新房间
	room[num][x] = 1;
	dfs(x+1, num+1);
	room[num][x] = 0;
}

void solve() {
	ans = n+1;
	dfs(1, 0);

	cout << ans << endl;
}

int main() {
	cin >> n >> m;

	int a, b;
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	solve();

	return 0;
}
