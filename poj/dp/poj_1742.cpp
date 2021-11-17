// POJ 1742 Coins
/*
	思路：
	dp[i][j] 考虑第 i 个以及之前的硬币凑 j 块钱 i 硬币还剩几个
	一个一个硬币考虑，i-1个硬币可以凑出来的金额，直接传递到 i
	之后 i 硬币用 1,2....，cnt[i] 个 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 110;
const int maxm = 100010;

int n, m;
int coins[maxn];
int cnt[maxn];
int dp[2][maxm];

void solve() {
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0; dp[1][0] = 0;
	
	int cur = 1, pre = 0;
	for(int i = 0; i < n; i++) {
		cur = (pre+1) % 2;
		for(int j = 0; j <= m; j++) {
			if(dp[pre][j] >= 0) {
				dp[cur][j] = cnt[i];
			} else if(j-coins[i] < 0 || dp[cur][j-coins[i]] <= 0) {
				dp[cur][j] = -1;
			} else {
				dp[cur][j] = dp[cur][j-coins[i]]-1;
			}
		}
		pre = cur;
	}
	int ans = 0;
	for(int j = 1; j <= m; j++)
		if(dp[pre][j] >= 0) ans++;

	cout << ans << endl;
}

int main() {
	while(cin >> n >> m && n && m) {
		for(int i = 0; i < n; i++) scanf("%d", &coins[i]);
		for(int i = 0; i < n; i++) scanf("%d", &cnt[i]);
		solve();
	}

	return 0;
}
