// 铺砖问题
/*
	n * m 个格子，用 1 * 2 的砖块，覆盖所有白色，不覆盖黑色，求方案数

	思路：
	状压dp
	用的是 1 * 2 的砖块，如果是 横着放 则影响下一个的状态
								竖着放 则影响下一行所对应的状态
	所以只需要保留上 m 个格子的状态即可

	dp[2][S]，滚动数组，S 为 上 m 个砖块的状态
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 16;

int n, m, G[maxn][maxn];
int dp[maxn][1 << maxn];

void dfs(int i, int j, int state, int nex) {
//	cout << i << j << endl;
	if(j == m) {
		dp[i+1][nex] += dp[i][state];
		return;
	}

	if(G[i][j] == 1 || ((1 << j) & state) == 1) {
		dfs(i, j+1, state, nex);
	}

	// 1 1
	if( ((1 << j) & state) == 0 && G[i][j] == 0 && (j+1) < m && ((1 << (j+1)) & state) == 0 && G[i][j+1] == 0 ) {
		dfs(i, j+2, state, nex);
	}

	/*
		1
		1
	*/
	if( ((1 << j) & state) == 0 && G[i][j] == 0 && ((1 << j) & nex) == 0 && G[i+1][j] == 0 ) {
		dfs( i, j+1, state, nex | (1 << j) );
	}
}

void solve() {
	dp[0][0] = 1;
	for(int i = 0; i < n; i++) {
		for(int S = 0; S < (1 << m); S++) {
			dfs(i, 0, S, 0);
		}
	}
//	for(int i = 0; i < n; i++) {
//		for(int S = 0; S < (1 << m); S++) {
//			printf("%d ",dp[i][S]);
//		}
//		printf("\n");
//	}
	cout << dp[n][0] << endl;
}

int main () {
	n = 3, m = 3;
	G[1][1] = 1;
	solve();

	return 0;
}
