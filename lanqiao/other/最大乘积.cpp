// 最大乘积 
/*

*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 20;

int n, m;
int dp[maxn][maxn][2];
int a[maxn];

//void solve() {
//	memset(dp, 0, sizeof(dp));
//	for (int i = 0; i <= n; i++) {
//		for (int k = 0; k < 2; k++) {
//			dp[i][0][k] = 1;
//		}
//	}
//	
//	for (int i = 1; i <= n; i++) {
//		for (int j = 1; j <= m; j++) {
//			dp[i][j][0] = dp[i-1][j][0];
//			dp[i][j][1] = dp[i-1][j][1];
//			
//			if (a[i] > 0) {
//				dp[i][j][0] = max(dp[i][j][0], dp[i-1][j-1][0]*a[i]);
//				dp[i][j][1] = min(dp[i][j][1], dp[i-1][j-1][1]*a[i]);
//			} else if (a[i] < 0) {
//				dp[i][j][0] = max(dp[i][j][0], dp[i-1][j-1][1]*a[i]);
//				dp[i][j][1] = min(dp[i][j][1], dp[i-1][j-1][0]*a[i]);
//			}
//		} 
//	}
//	
//	cout << dp[n][m][0] << endl;
//} 

void solve2() {
	int lim = 1<<n;
	
	int ans = INT_MIN;
	for (int s = 0; s < lim; s++) {
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if ((1<<i) & s) cnt++;
		}
		if (cnt != m) continue;
		
		int cur = 1;
		for (int i = 0; i < n; i++) {
			if ((1<<i) & s) {
				cur *= a[i];
			}
		}
		ans = max(ans, cur);
	}
	
	cout << ans << endl;
}

int main() {
	int T;
	cin >> T;
	cout << -0x7fffffff;
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++) scanf("%d", &a[i]);
		solve2();
	}
	
	return 0;
}
