// 蓝桥杯国赛集训-----排兵布阵
/*

*/

#include <bits/stdc++.h>

using namespace std;

int s, n, m;
vector<vector<int> > dp;
vector<vector<int> > nums;

void solve() {
	for (int i = 1; i <= n; i++) {
		sort(nums[i].begin()+1, nums[i].end());
	}

	dp = vector<vector<int> > (n+1, vector<int>(m+1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j] = dp[i-1][j];
			for (int k = 1; k <= s; k++) {
				if (j > 2*nums[i][k]) {
					dp[i][j] = max(dp[i][j], dp[i-1][j-2*nums[i][k]-1]+k*i);
				}
			}
		}
	}

	int ans = 0;
	for (int j = 1; j <= m; j++) {
		ans = max(ans, dp[n][j]);
	}
	cout << ans << endl;
}

int main() {
	cin >> s >> n >> m;
	nums = vector<vector<int> > (n+1, vector<int>(s+1, 0));
	for (int i = 1; i <= s; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &nums[j][i]);
		}
	}
	solve();

	return 0;
}
