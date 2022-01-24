// 蓝桥杯11B 走方格 
/*
	思路：
	dp 
*/

#include <bits/stdc++.h>

using namespace std;

int dp[35][35];

int main() {
	int n, m;
	cin >> n >> m;
	
	dp[1][1] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(i%2==0 && j%2==0) continue;
			if(i==1 && j==1) continue;
			dp[i][j] = dp[i-1][j] + dp[i][j-1];
		}
	}
	cout << dp[n][m] << endl;
	
	return 0;
} 
