// 多重集组合数
/*
	有 n 个物品，每个物品有 ai 件，取出 m 件，求情况数

	dp[i][j] 表示 物品有 i 件，取 j 件的情况数

	dp[i+1][j] = sum(dp[i][j-k]) ( k:0,1,...min(ai,j) ) ai的 i 从0开始
	时间复杂度 O(sum(ai)*m) 时间复杂度过高

	优化
	对式子右边展开
	1. j <= ai dp[i+1][j] = dp[i+1][j-1] + dp[i][j]
	2. ai < j  dp[i+1][j] = dp[i+1][j-1] + dp[i][j] - dp[i][j-1-a[i]]
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 1010;
const int maxm = 1010;

int n, m, mod;
int dp[maxn][maxm];
int a[maxn];

void solve() {
	memset(dp,0,sizeof(dp));

	for(int i=0; i<=n; i++) dp[i][0] = 1;
	for(int i=0; i<n; i++) {
		for(int j=1; j<=m; j++) {
			if(j-1-a[i] >= 0)
				dp[i+1][j] = (dp[i+1][j-1] + dp[i][j] - dp[i][j-1-a[i]]) % mod;
			else
				dp[i+1][j] = (dp[i+1][j-1] + dp[i][j]) % mod;
		}
	}

	cout << dp[n][m];
}

int main() {
	while(cin >> n >> m >> mod) {
		for(int i=0; i<n; i++) {
			scanf("%d", &a[i]);
		}

		solve();
	}

	return 0;
}
