// POJ 2184 Cow Exhibition
/*
	思路：
	处理负数的 01 背包 
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 110;
const int maxm = 2e5+10;
const int sh = 1e5;

int n, s[maxn], f[maxn];
int dp[maxm];

void solve() {
	for(int j = 0; j < maxm; j++) {
		dp[j] = -INF;
	}

	dp[sh] = 0;
	for(int i = 1; i <= n; i++) {
		if(s[i] > 0) {
			for(int j = maxm-1; j-s[i] >= 0; j--) {
				dp[j] = max(dp[j], dp[j-s[i]]+f[i]);
			}
		} else {
			for(int j = 0; j-s[i] < maxm; j++) {
				dp[j] = max(dp[j], dp[j-s[i]]+f[i]);
			}
		}
	}

	int ans = 0;
	for(int j = sh; j < maxm; j++) if(dp[j] > 0) ans = max(ans, j-sh+dp[j]);

	cout << ans << endl;
}

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &s[i], &f[i]);
	}
	solve();

	return 0;
}
