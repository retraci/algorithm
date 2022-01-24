// 蓝桥杯2019B F最优包含
/*
	思路：
	dp
	编辑距离的变形 
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1010;

int dp[maxn][maxn];

int main() {
	string s, t;
	cin >> s >> t;

	int n = s.size();
	int m = t.size();
	memset(dp, 0x3f3f3f3f, sizeof(dp));
	for(int i = 0; i <= n; i++) dp[i][0] = 0;
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(s[i-1] == t[j-1]) dp[i][j] = dp[i-1][j-1];
			else dp[i][j] = min(dp[i-1][j], dp[i-1][j-1]+1);
		}
	}
	cout << dp[n][m] << endl;

	return 0;
}
