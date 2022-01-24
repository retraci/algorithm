// 数数
/*

*/

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int maxn = 1e6+10;
const ll MOD = 1e16;

int n;
ll dp[maxn][4][3];

void solve() {
	memset(dp, 0, sizeof(dp));
	
	int flag = 0;
	dp[1][1][1] = dp[1][2][1] = dp[1][3][1] = 1;
	for (int i = 2; i <= n; i++) {
		for (int a = 1; a <= 3; a++) {
			for (int j = 1; j <= 3; j++) {
				if (a == j) continue;
				for (int len = 1; len < 3; len++) {
					if (!flag && dp[i][a][1]+dp[i-1][j][len] >= MOD) flag = 1;
					dp[i][a][1] = (dp[i][a][1]+dp[i-1][j][len]) % MOD;
				}
			}
			dp[i][a][2] = dp[i-1][a][1];
		}
	}
	
	long long ans = 0;
	for (int a = 1; a <= 3; a++) {
		for (int len = 1; len < 3; len++) {
			if (!flag && ans+dp[n][a][len] >= MOD) flag = 1;
			ans = (ans+dp[n][a][len]) % MOD;
		}
	}
	if (!flag) cout << ans << endl;
	else cout << "......" << ans % (ll)(1e10) << endl;
}

int main() {
	cin >> n;
	solve();

	return 0;
}
