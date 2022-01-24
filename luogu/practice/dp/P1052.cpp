// P1052 过河
/*

*/

#include <bits/stdc++.h>

using namespace std;

const int MX = 90;
const int M = 110;
const int N = MX * M;

int L, s, t, m;
int st[M];
int n;
int lsh[M], has[N];
int dp[N];

void solve() {
	sort(st + 1, st + 1 + m);
	
	if (s == t) {
		int ans = 0;
		for (int i = 1; i <= m; i++) ans += st[i] % s == 0;
		cout << ans << endl;
		return;
	}
	
	for (int i = 1; i <= m; i++) {
		int d = st[i] - st[i-1];
		if (d > MX) d = MX;
		lsh[i] = lsh[i-1] + d;
		has[lsh[i]] = 1;
	}
	n = lsh[m] + MX;
	
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = s; j <= t; j++) {
			if (i - j < 0) break;			
			if (has[i]) dp[i] = min(dp[i], dp[i-j] + 1);
			else dp[i] = min(dp[i], dp[i-j]);
		}
	}
	
	int ans = 1000;
	for (int i = lsh[m] + 1; i <= n; i++) ans = min(ans, dp[i]);
	
	cout << ans << endl;
}

int main() {
	cin >> L >> s >> t >> m;
	for (int i = 1; i <= m; i++) cin >> st[i];
	solve();
	
	return 0;
}

