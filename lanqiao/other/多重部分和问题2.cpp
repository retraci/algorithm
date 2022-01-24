// 多重部分和问题2
/*
	思路转化
	dp[i+1][j] 表示前 i 种数累加得 j 时，第 i 种数剩多少个 ( i 从 0 开始)

	初始化 -1
	若 dp[i][j] >= 0 则 dp[i+1][j] = m[i] 直接继承
	若 dp[i][j] < 0 则 考虑用 a[i+1]
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 110;
const int maxk = 1e5+10;

int n, K;
int a[maxn], m[maxn];
int dp[maxn][maxk];

void solve() {
	memset(dp,-1,sizeof(dp));

	dp[0][0] = 0;
	for(int i=0; i<n; i++) {
		for(int j=0; j<=K; j++) {
			if(dp[i][j] >= 0) {
				dp[i+1][j] = m[i];
			} else if(dp[i+1][j-a[i]] >= 0) {
				dp[i+1][j] = dp[i+1][j-a[i]]-1;
			} else {
				dp[i+1][j] = -1;
			}
		}
	}

	cout << dp[n][K] << endl;
}

int main() {
	while(cin >> n >> K) {
		for(int i=0; i<n; i++) {
			scanf("%d", &a[i]);
		}

		for(int i=0; i<n; i++) {
			scanf("%d", &m[i]);
		}

		solve();
	}

	return 0;
}
