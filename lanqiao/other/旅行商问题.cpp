// 旅行商问题
/*
	从 0 开始经过所有点恰好一次，回到 0 消费代价

	思路：
	状压 dp
	dp[S][v]，S 表示剩下的点，v 表示从 v 出发，dp 表示从 v 出发回到 0 的最小代价

	倒着推，或者用递归
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 15;

int n, d[maxn][maxn], dp[1 << maxn][maxn];

void solve() {
	memset(dp, INF, sizeof(dp));
	dp[(1 << n) - 1][0] = 0;

	for(int S = (1 << n) - 2; S >= 0; S--) {
		for(int v = 0; v < n; v++) {
			for(int u = 0; u < n; u++) {
				// 走到 v 的时候需要 u 没走过 
				if(!(S & 1 << u)) {
					dp[S][v] = min(dp[S][v], dp[S | 1 << u][u] + d[v][u]);
				}
			}
		}
	}
	printf("%d\n", dp[0][0]);
}

int main() {
	n = 5;
	memset(d, INF, sizeof(dp));
	d[0][1] = 3, d[0][3] = 4;
	d[1][2] = 5;
	d[2][0] = 4, d[2][3] = 5;
	d[3][4] = 3;
	d[4][0] = 7, d[4][1] = 6;
	solve();

	return 0;
}
